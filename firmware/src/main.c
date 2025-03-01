#include "sys/socket.h"
#include "freertos/FreeRTOS.h"
#include "measurement.h"

void app_main() {

    //desarrollar manejo de config.json

    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
    adc1_config_width(ADC_WIDTH_BIT_12); 
    

}