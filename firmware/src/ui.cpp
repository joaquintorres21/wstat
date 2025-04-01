#include <controller.h>
#include <display.h>

void interface(Adafruit_SH1106G& display, meteor_data data, state_t global, state_t chill){
    
    char calibrating_mq = 1;
    double t_minus;

    display.setCursor(0,10);
    display.setTextSize(2);
    display.println("# WSTAT #");
    display.setTextSize(1);

    if(chill) display.setContrast(127);
    else display.setContrast(255);

    write_page(display, data, global);

    display.setCursor(59,64);
    display.print("&");
    display.setCursor(71,64);
    display.print("$");

}

void write_page(Adafruit_SH1106G& display, meteor_data data, state_t global){
    
    switch(global){

        case 0: 
        display.printf("Temperatura: %.1f}C\\0.1}C\n", data.temperature);
        display.printf("Humedad: %.1f/\\0.1/\n", data.humidity);
        display.printf("Indice de calor: %.2f}C\n", data.heat_index);
        display.printf("CO_2: %.0fppm", data.co2);
        display.display();
        break;

        case 1: 
        display.printf("Presion: %fPa\n", data.pressure);
        display.printf("Viento: fkm/h\n");
        display.printf("Viento: f}[dir]\n");
        display.printf("Punto de rocio: f\n");
        break;
        
        case 2:
        display.printf("Altitud: fm\n");
        display.printf("Densidad del aire: fg/cm3\n");
        display.printf("Evapotranspiracion: f\n");
        display.printf("Altura de las nubes: fm\n");
        break;

        case 3:
        display.printf("Temperatura eq. pot.: f}\n");
        display.printf("Humedad especifica: f\n");
        display.printf("Humidex: f\n");
        display.printf("Flujo de calor sensible: f\n");
        break;
    }
}