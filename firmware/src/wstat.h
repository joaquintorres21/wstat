#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Org_01.h>

#include <Adafruit_SH110X.h>

#define VCC 5.0 // Supply voltage
#define CURRENT_RESOLUTION 12 //Bits

//Empirical constants provided by NWS to calculate heat index. https://en.wikipedia.org/wiki/Heat_index#Formula
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

typedef float mq_data;

typedef struct {

    float humidity;
    float temperature;
    float air_quality;
    float heat_index; 
    float pressure;

}meteor_data;

meteor_data construct(dht_data,  mq_data, bmp_data);

meteor_data testConstruct(dht_data dht_data);

void interface(Adafruit_SH1106G*, meteor_data);

float to_celsius(float grade_in_f);

dht_data dht_get(uint8_t dht_pin);

mq_data mq_get(uint8_t mq_pin);

bmp_data bmp_get(uint8_t bmp_pin);

