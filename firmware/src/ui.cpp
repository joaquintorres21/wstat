#include <controller.h>
#include <display.h>


void interface(Adafruit_SH1106G& display, meteor_data data, state_t global){
    
    char calibrating_mq = 1;
    double t_minus;

    display.setCursor(0,10);
    display.setTextSize(2);
    display.println("# WSTAT #");
    display.setTextSize(1);

    write_page(display, data, global);

    display.setCursor(59,64);
    display.print("&");
    display.setCursor(71,64);
    display.print("$");

}

void write_page(Adafruit_SH1106G& display, meteor_data data, state_t global){
    
    switch(global){
        
        case -1:
        display.printf("IP: %d.%d.%d.%d\n");
        display.printf("Port: %d");
        display.printf("Tiempo %d:%d");
        break;
        
        case 0: 
        display.printf("Temperatura: %.1f}C\\0.1}C\n", data.temperature);
        display.printf("Humedad: %.1f/\\0.1/\n", data.humidity);
        display.printf("Indice de calor: %.2f}C\n", data.heat_index);
        display.printf("CO_2: %.0fppm", data.co2);
        display.display();
        break;

        case 1: 
        display.printf("Presion: %funidad\n", data.pressure);
        display.printf("R_S[MQ135]: fkOhm\n");
        display.printf("Consumo: fmA\n");
        break;
        
    }
}