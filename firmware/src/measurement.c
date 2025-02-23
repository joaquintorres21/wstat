#include "driver/gpio.h"
#include "esp_timer.h"
#include "measurement.h"

dht_data dht_get(uint8_t pin){

    dht_data measurement;
    //proceso de comunicacion... a desarrollar
    
    

    uint16_t sigma = measurement.r_hum + measurement.r_temp + measurement.z_hum + measurement.z_temp;
    if(sigma != measurement.checksum) return;
    return measurement;

}

float* dht_convert(dht_data raw, float* v_2d){

    float humidity = raw.z_hum + raw.r_hum/100.0;
    float temperature = raw.z_temp + raw.r_temp/100.0;
    v_2d[0] = humidity;
    v_2d[1] = temperature;
    return v_2d;

}