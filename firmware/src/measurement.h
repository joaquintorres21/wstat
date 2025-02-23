#include <stdint.h>

#define DHT_HOST 1000 //Activation lapse 
#define DHT_PULSE 80 //Response sent by the sensor indicating that it's going 
#define DHT22_PULSE 27 //

#define ERROR 1

//DHT sends data in 40 bits, with an integer and a decimal part for each variable
typedef struct {

    uint8_t z_hum; //Humidity integer part
    uint8_t r_hum; //Humidity decimal part
    uint8_t z_temp; //Temperature integer part
    uint8_t r_temp; //Temperature decimal part
    uint8_t checksum; //Previous 4 bytes sum

} dht_data;

//Manages comms between the controller and sensor, returns raw data
dht_data dht_get(uint8_t pin);

//Returns a floating-point vector v = (humidity, temperature)
float* dht_convert(dht_data, float*);

