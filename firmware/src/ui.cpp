#include <controller.h>
#include <display.h>


void interface(Adafruit_SH1106G* display, meteor_data data, float r0){
    
    char calibrating_mq = 1;
    double t_minus;

    (*display).setCursor(0,10);
    (*display).setTextSize(2);
    (*display).println("# WSTAT #");
    (*display).setTextSize(1);
    
    (*display).printf("Temperatura: %.1f}C\\0.1}C\n", data.temperature);
    (*display).printf("Humedad: %.1f/\\0.1/\n", data.humidity);
    (*display).printf("Indice de calor: %.2f}C\n", data.heat_index);
    if(calibrating_mq && (t_minus = clock() / CLOCKS_PER_SEC) < 300) {
        (*display).printf("CO_2: Calibrando. t = %f segundos", t_minus);
    } else {
        (*display).printf("CO_2: %.0f", data.co2);
        calibrating_mq = 0;
    }
    (*display).printf("RS: %.3fk", r0);
    
    (*display).display();

}