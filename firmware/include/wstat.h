#pragma once

#include <wtypes.h>

#define VCC 5.0 // Supply voltage
#define CURRENT_RESOLUTION 12 //Bits
#define MU_TO_MINUS_ONE 9999 //High value

//MQ 135 Load SMD resistance. 203 = 20E3 = 20K. Precisely measured with multimeter.
const float R_L = 19.6;

//Empirical constants provided by NWS to calculate heat index based on temperature and RH (converted to celsius). https://en.wikipedia.org/wiki/Heat_index#Formula
const double hic[9]=
{
    -8.7846947,
    1.6113941,
    2.3385488,
    -0.14611605,
    -0.0123080,
    -0.0164248,
    0.0022117,
    0.0007254,
    -0.0000035
};

//Linear regression constants for CO2 sensibility curve. PPM = 116.6 * (RS/R0)^-2.769.
const float co_2[2] = {
    116.6,
    -2.769
};

//Converts to Fahrenheit a Celsius input. 
float to_fahrenheit(float grade_in_c) {return grade_in_c*1.8+32;}

//Returns resistance R_0 that is R_s when measured in a room with 400ppm of CO2.
float mq_calibrate(uint8_t mq_pin);

//Returns dht_data type.
dht_data dht_get(uint8_t dht_pin);

//Returns mq_data type
mq_data mq_get(uint8_t mq_pin, float r_0);

//Returns bmp_data type
bmp_data bmp_get(uint8_t bmp_pin);

//Generates data received by display and HMI.
meteor_data construct(dht_data, mq_data, bmp_data);