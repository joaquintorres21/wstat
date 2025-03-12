#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Org_01.h>

#include <Adafruit_SH110X.h>

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
    uint16_t h;
    uint16_t t;

}dht_data;

typedef struct {

    float humidity;
    float temperature;
    float air_quality;
    float heat_index; 
    float pressure;

}meteor_data;

meteor_data measurements(
    uint8_t dht_pin, 
    uint8_t mq_pin, 
    uint8_t bmp_data_pin, 
    uint8_t bmp_clock_pin);

void interface(Adafruit_SH1106G, meteor_data);

dht_data dht_get(uint8_t dht_pin);

void testInterface(Adafruit_SH1106G screen, dht_data data);