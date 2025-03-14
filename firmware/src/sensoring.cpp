#include "wstat.h"
#include "esp_timer.h"
#include "driver/adc.h"

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
    pinMode(dht, INPUT_PULLUP);

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

mq_data mq_get(uint8_t adc_pin){

    mq_data data;
    uint16_t voltage_data = VCC * analogRead(adc_pin);
    
    //interpretacion. por ahora data = voltage_data
    data = voltage_data*1.0 / adc_res(CURRENT_RESOLUTION);

    return data;    

}

bmp_data bmp_comms(uint8_t bmp){

}

bmp_data bmp_get(uint8_t bmp){

}