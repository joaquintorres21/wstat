#pragma once

#include <stdint.h>

//Refeers to a state type, depends on the selected page.
typedef char state_t;

//DHT22 sends data in 40 bits, each byte represents integer and decimal part of each measured variable.
//Fifth byte represents checksum, where z_h + z_t + r_h + r_t should be equal to it.
typedef struct {
    
    uint8_t z_h;
    uint8_t z_t;
    uint8_t r_h;
    uint8_t r_t;

    uint16_t humidity;
    uint16_t temperature;

}dht_data;

//MQ sends an analogic value representing an measurement of all the gases pressing it.
typedef float mq_data;

typedef struct {
    
    uint32_t temperature;
    uint32_t pressure;
    
}bmp_data;

//This data type is built and sent to the onboard display, and to the desktop HMI.
typedef struct {

    float humidity;
    float temperature;
    float co2;
    float heat_index; 
    float pressure;

}meteor_data;