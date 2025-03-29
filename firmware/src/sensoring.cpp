#include <wstat.h>
#include <Wire.h>
#include <HardwareSerial.h>

uint16_t adc_res(uint16_t i){
    if(!i) return 1;
    return pow(2,i-1) + adc_res(i-1);
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


bmp_data bmp_get(uint16_t bmp_add){
    
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


    //Raw data. Needs to be calibrated with internal parameters dig_t(n) / dig_p(n)
    data.pressure = ((uint32_t)pres_msb << 12) | ((uint32_t)pres_mb << 4) | (pres_lsb >> 4);
    data.temperature = (temp_msb << 8) | temp_lsb;

    return data;

}

//Intended to be executed just once since they are constants
bmp_const bmp_parameters(uint16_t bmp_add){
    
    bmp_const parameters;

    Wire.beginTransmission(bmp_add);
    Wire.write(0x88);
    Wire.endTransmission();

    Wire.requestFrom(bmp_add, 24);
    parameters.dig_T1 = Wire.read() | (Wire.read() << 8);
    parameters.dig_T2 = (int16_t)(Wire.read() | (Wire.read() << 8));
    parameters.dig_T3 = (int16_t)(Wire.read() | (Wire.read() << 8));
    parameters.dig_P1 = Wire.read() | (Wire.read() << 8);
    parameters.dig_P2 = (int16_t)(Wire.read() | (Wire.read() << 8));
    parameters.dig_P3 = (int16_t)(Wire.read() | (Wire.read() << 8));
    parameters.dig_P4 = (int16_t)(Wire.read() | (Wire.read() << 8));
    parameters.dig_P5 = (int16_t)(Wire.read() | (Wire.read() << 8));
    parameters.dig_P6 = (int16_t)(Wire.read() | (Wire.read() << 8));
    parameters.dig_P7 = (int16_t)(Wire.read() | (Wire.read() << 8));
    parameters.dig_P8 = (int16_t)(Wire.read() | (Wire.read() << 8));
    parameters.dig_P9 = (int16_t)(Wire.read() | (Wire.read() << 8));
    
    return parameters;

}

bmp_data bmp_process(bmp_data& raw, bmp_const param){
    
    int32_t adjt_1, adjt_2;
    int64_t adjp_1, adjp_2, p;
    adjt_1 = (((raw.temperature >> 3) - ((int32_t)param.dig_T1<<1))) * ((int32_t)param.dig_T2) >> 11;
    adjt_2 = (((((raw.temperature >> 4) - ((int32_t)param.dig_T1)) * ((raw.temperature >> 4) - ((int32_t)param.dig_T1))) >> 12) * 
    ((int32_t)param.dig_T3)) >> 14;

    raw.temperature = (((adjt_1 + adjt_2) * 5 + 128) >> 8) / 1000;

    adjp_1 = ((int64_t)adjt_1+adjt_2) - 128000;
    adjp_2 = adjp_1 * adjp_1 * (int64_t)param.dig_P6;
    adjp_2 += ((adjp_1*(int64_t)param.dig_P5)<<17);
    adjp_2 += ((int64_t)param.dig_P4<<35);
    adjp_1 = ((adjp_1*adjp_1*(int64_t)param.dig_P3)>>8) + ((adjp_1 * (int64_t)param.dig_P2)<<12);
    adjp_1 = (((((int64_t)1)<<47)+adjp_1)) * ((int64_t)param.dig_P1)>>33;

    if(!adjp_1) return raw;
    
    p = 1048576 - raw.pressure;
    p = (((p<<31)-adjp_2)*3125) / adjp_1;
    adjp_1 = (((int64_t)param.dig_P9) * (p>>13) * (p >> 13)) >> 25;
    adjp_2 = (((int64_t)param.dig_P8) * p) >> 19;
    p = ((p + adjp_1 + adjp_2)>> 8) + (((int64_t)param.dig_P7)<<4);
    
    raw.pressure = (uint32_t)p / 25600;
    
    return raw;
    
}