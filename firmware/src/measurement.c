#include "measurement.h"


//natural power function
int z_pow(int a, int x){
    if(!x) return 1;
    a = a * pow(a, x-1);
    return a;
}

void IRAM_ATTR dht_check(uint8_t* state){
    return *state = gpio_get_level(PIN_DHT);
}

float* dht_convert(dht_data raw, float* v_2d){

    float humidity = raw.z_hum + raw.r_hum/100.0;
    float temperature = raw.z_temp + raw.r_temp/100.0;
    v_2d[0] = humidity;
    v_2d[1] = temperature;
    return v_2d;

}

dht_data dht_get(uint8_t dht_pin){

    int delay;
    uint8_t sensor_reading = 0;
    uint8_t significance = 1;
    dht_data measurement;
    esp_timer_handle_t t_get, t_none;
    uint16_t* current_variable[4];
    current_variable[0] = &(measurement.z_hum);
    current_variable[1] = &(measurement.r_hum);
    current_variable[2] = &(measurement.z_temp);
    current_variable[3] = &(measurement.r_temp);
    
    const esp_timer_create_args_t get_state_timer = {
        .callback = &dht_check,
        .arg = &sensor_reading,
        .name = "check0"
    };
    
    const esp_timer_create_args_t none_timer = {
        .callback = NULL,
        .name = "default"
    };

    esp_timer_create(&get_state_timer, &t_get);
    esp_timer_create(&none_timer, &t_none);

    //comm between esp and dht
    gpio_set_direction(dht_pin, GPIO_MODE_OUTPUT);
    gpio_set_level(dht_pin, LOW);
    vTaskDelay(pdMS_TO_TICKS(1000));
    gpio_set_level(dht_pin, HIGH);

    gpio_set_direction(dht_pin, GPIO_MODE_INPUT); //pin is set to floating point voltage to receive data
    esp_timer_start_once(t_get, 40);
    if(sensor_reading != 0) return; //fatal error
    esp_timer_start_once(t_get, 80);
    if(sensor_reading != 1) return; //...

    uint8_t var_index = 0;
    while(significance <= BITS_PER_BYTE){

        esp_timer_start_once(t_none, DHT_AVERAGE);
        
        **(current_variable + var_index) |= (sensor_reading << BITS_PER_BYTE - significance);

        significance++;
        
        if(sensor_reading) esp_timer_start_once(t_none, DHT_HIGH_TIMEOUT);
        else esp_timer_start_once(t_none, DHT_LOW_TIMEOUT);
        
        //If the position is out of range we go back to 0 until there are no variables left to save.
        if(significance > BITS_PER_BYTE){
            if(var_index == 3) break;
            var_index++;
            significance = 0;
        }
        
    }

    uint16_t sigma = measurement.r_hum + measurement.r_temp + measurement.z_hum + measurement.z_temp;
    if(sigma != measurement.checksum) return;
    return measurement;

}

mq_data mq_get(uint8_t mq_pin){

    uint16_t adc_reading = adc1_get_raw(ADC_CHANNEL_0);
    float adc_in_volts = VCC * adc_reading / RES_12BITS;

    //calibrar e interpretar voltaje a co2
    mq_data co2; //= ecuacion desconocida 
    return co2;

}


