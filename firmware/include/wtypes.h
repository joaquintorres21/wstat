#pragma once

#include <stdint.h>

//Refeers to a state type, depends on the selected page.
typedef signed char state_t;

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


//Internal parameters from the BMP280 registers used to process the raw data.
typedef struct {
    
    unsigned short dig_T1;
    short dig_T2;
    short dig_T3;
    unsigned short dig_P1;
    short dig_P2;
    short dig_P3;
    short dig_P4;
    short dig_P5;
    short dig_P6;
    short dig_P7;
    short dig_P8;
    short dig_P9;
    
}bmp_const;

//This data type is built and sent to the onboard display, and to the desktop HMI.
typedef struct {

    float humidity;
    float temperature;
    float co2;
    float heat_index; 
    float pressure;

}meteor_data;