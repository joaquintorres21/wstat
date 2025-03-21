#include <wstat.h>
#include <Wire.h>

uint16_t adc_res(uint16_t i){
    if(!i) return 1;
    return pow(2,i-1) + adc_res(i-1);
}

void begin_adc(uint8_t mq_pin){

}

char dht_comms(uint8_t dht){
    
    pinMode(dht, OUTPUT);
    GPIO.out_w1tc = (1 << dht);

    delayMicroseconds(1500);
    pinMode(dht, INPUT);

    //Here the sensor should send a 0 to the MCU.
    while((((GPIO.in & (1 << dht)) >> dht) & 1));
    
    //""""""...1 to the MCU.
    while(!(((GPIO.in & (1 << dht)) >> dht) & 1));

    while((((GPIO.in & (1 << dht)) >> dht) & 1));

    return 0;

}

dht_data dht_get(uint8_t dht){
    
    uint8_t bit;
    uint8_t checksum;

    uint8_t index = 1;
    uint8_t var = 1;
    int64_t t0;
    uint8_t delta_index;
    dht_data data = {0,0,0,0,0,0};

    dht_comms(dht);

    while(index < 40){

        while(!(((GPIO.in & (1 << dht)) >> dht) & 1));
        t0 = esp_timer_get_time();

        while((((GPIO.in & (1 << dht)) >> dht) & 1));
        bit = (esp_timer_get_time()-t0) > 40 ? 1 : 0;

        delta_index = 8*var - index;
        
        switch(var){
            case 1: data.z_h |= (bit << delta_index); break;
            case 2: data.r_h |= (bit << delta_index); break;
            case 3: data.z_t |= (bit << delta_index); break;
            case 4: data.r_t |= (bit << delta_index); break;
        }
        
        if(delta_index==0) var++;
        index++;

    }

    data.humidity = (data.z_h << 8) | data.r_h;
    data.temperature = (data.z_t << 8) | data.r_t;

    return data;
}

//Use on an environment with 400ppm CO2. Then put the value as second arg in mq_get
float mq_calibrate(uint8_t adc_pin){
    float voltage_data;
    int resolution = adc_res(CURRENT_RESOLUTION);
    //Sensor internal resistance during a certain measurement.
    float r_0;
    
    for(int i = 0; i < 25; i++) voltage_data += (float) analogRead(adc_pin);
    voltage_data /= 25.0;
    voltage_data *= VCC / resolution;
    r_0 =  ((float)R_L * (VCC - voltage_data)/voltage_data);

    return r_0;
}

mq_data mq_get(uint8_t adc_pin, float r_0){

    mq_data voltage_data = 0.0;
    int resolution = adc_res(CURRENT_RESOLUTION);

    //Sensor internal resistance during a certain measurement.
    float r_s, ratio;
    
    for(int i = 0; i < 10; i++) voltage_data += (float) analogRead(adc_pin);
    
    voltage_data /= 10.0;
    voltage_data *= VCC/4096.0;
    r_s = R_L * (VCC - voltage_data)/voltage_data;
    ratio = r_s / r_0;
    
    //Exponential adjustment to the measurements.
    voltage_data = co_2[0] * pow(ratio, co_2[1]);
    return voltage_data;

}


bmp_data bmp_get(uint8_t bmp_add){
    
    bmp_data data;
    char bytes;
    uint8_t temp_msb, temp_lsb, pres_msb, pres_mb, pres_lsb;

    Wire.beginTransmission(bmp_add);
    Wire.write(BMP_PRESSURE);
    Wire.endTransmission();
    
    Wire.requestFrom(bmp_add, 3);
    pres_msb = Wire.read();
    pres_mb = Wire.read();
    pres_lsb = Wire.read();

    Wire.beginTransmission(bmp_add);
    Wire.write(BMP_TEMPERATURE);
    Wire.endTransmission();

    Wire.requestFrom(bmp_add, 2);
    temp_msb = Wire.read();
    temp_lsb = Wire.read();
    
    data.pressure = ((uint32_t)pres_msb << 12) | ((uint32_t)pres_mb << 4) | (pres_lsb >> 4);
    data.temperature = (temp_msb << 8) | temp_lsb;

    return data;

}