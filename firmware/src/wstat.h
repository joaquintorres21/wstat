#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Org_01.h>
#include <Adafruit_SH110X.h>

#define VCC 5.0 // Supply voltage
#define CURRENT_RESOLUTION 12 //Bits

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

//Linear regression constants for CO2 sensibility curve. PPM = 116.6 * (RS/R0)^-2.769
const float co_2[2] = {
    116.6,
    -2.769
};

//DHT22 sends data in 40 bits, each byte represents integer and decimal part of each measured variable.
typedef struct {
    
    uint8_t z_h;
    uint8_t z_t;
    uint8_t r_h;
    uint8_t r_t;
    uint16_t humidity;
    uint16_t temperature;

}dht_data;

typedef struct {
    
    uint32_t temperature;
    uint32_t pressure;
    
}bmp_data;

//MQ sends an analogic value representing an measurement of all the gases pressing it.
typedef float mq_data;

//This data type is built and sent to the onboard display, and to the desktop HMI.
typedef struct {

    float humidity;
    float temperature;
    float co2;
    float heat_index; 
    float pressure;

}meteor_data;

meteor_data construct(dht_data, mq_data, bmp_data);

void interface(Adafruit_SH1106G*, meteor_data, float r0);

float to_celsius(float grade_in_f);

dht_data dht_get(uint8_t dht_pin);

float mq_calibrate(uint8_t mq_pin);

mq_data mq_get(uint8_t mq_pin, float r_0);

bmp_data bmp_get(uint8_t bmp_pin);

