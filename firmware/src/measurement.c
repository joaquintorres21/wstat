#include "measurement.h"

void IRAM_ATTR dht_check(uint8_t* state){
    return *state = gpio_get_level(PIN_DHT);
}

void dht_dep(int* x){
    return;
}

float* dht_convert(dht_data raw, float* v_2d){

    float humidity = raw.z_hum + raw.r_hum/100.0;
    float temperature = raw.z_temp + raw.r_temp/100.0;
    v_2d[0] = humidity;
    v_2d[1] = temperature;
    return v_2d;

}

dht_data dht_get(uint8_t pin){

    uint8_t st;
    dht_data measurement;
    esp_timer_handle_t t_get;

    const esp_timer_create_args_t get_state_timer = {
        .callback = &dht_check,
        .arg = &st,
        .name = "check0"
    };

    esp_timer_create(&get_state_timer, &t_get);

    //comm between esp and dht
    gpio_set_direction(PIN_DHT, GPIO_MODE_OUTPUT);
    gpio_set_level(PIN_DHT, LOW);
    vTaskDelay(pdMS_TO_TICKS(1000));
    gpio_set_level(PIN_DHT, HIGH);

    gpio_set_direction(PIN_DHT, GPIO_MODE_INPUT); //pin is set to floating point voltage to receive data
    esp_timer_start_once(t_get, 40);
    if(st != 0) return; //fatal error
    esp_timer_start_once(t_get, 80);
    if(st != 1) return; //...
    

    //a desarrollar receiving
    dht_dep(&(measurement.z_hum));
    dht_dep(&(measurement.r_hum));
    dht_dep(&(measurement.z_temp));
    dht_dep(&(measurement.r_temp));

    uint16_t sigma = measurement.r_hum + measurement.r_temp + measurement.z_hum + measurement.z_temp;
    if(sigma != measurement.checksum) return;
    return measurement;

}




