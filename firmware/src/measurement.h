#include <stdint.h>
#include "driver/gpio.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#define LOW 0
#define HIGH 1


#define DHT_HOST 1000 //Activation lapse 
#define DHT22_PULSE 80 //Response sent by the sensor indicating that it's going 
#define DHT22_LOW 27 //Low bit
#define DHT22_HIGH 70 //High bit

#define PIN_DHT 0
#define PIN_MQ //ADC pin needed

#define ERROR 1
//DHT sends data in 40 bits, with an integer and a decimal part for each variable
typedef struct {

    uint8_t z_hum; //Humidity integer part
    uint8_t r_hum; //Humidity decimal part
    uint8_t z_temp; //Temperature integer part
    uint8_t r_temp; //Temperature decimal part
    uint8_t checksum; //Previous 4 bytes sum

} dht_data;

typedef float mq_data; //Floating-point value received from the ADC, which is then converted into an air purity measurement.

//Manages comms between the controller and sensor, returns raw data
dht_data dht_get(uint8_t pin);

//Deposits in each one of the dht_data object properties its respective information.
void dht_dep(int *property);

//Returns a floating-point vector v = {humidity; temperature}
float* dht_convert(dht_data, float*);

void IRAM_ATTR dht_check(uint8_t* state);