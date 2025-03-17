#include "wstat.h"

meteor_data construct(dht_data dht_data, mq_data mq_data, bmp_data bmp_data){
    
    meteor_data measurements;
    
    float tt = bmp_data.temperature*bmp_data.temperature / 100.0;
    float hh = dht_data.humidity*dht_data.humidity / 100.0;
    float th = bmp_data.temperature*dht_data.humidity / 100.0;

    measurements.temperature = bmp_data.temperature / 10.0;
    measurements.humidity = dht_data.humidity / 10.0;

    measurements.heat_index = hic[0] + hic[1]*measurements.temperature + hic[2]*measurements.humidity + hic[3]*th+ 
    hic[4]*tt + hic[5]*hh + hic[6]*tt*measurements.humidity + hic[7]*measurements.temperature*hh + hic[8]*tt*hh; 
    
    measurements.pressure = bmp_data.pressure;
    measurements.co2 = mq_data;

    return measurements;
    
}

void interface(Adafruit_SH1106G* display, meteor_data data, float r0){
    
    (*display).setCursor(0,10);

    (*display).setTextSize(2);
    (*display).println("# WSTAT #");

    (*display).setTextSize(1);
    (*display).printf("Temperatura: %.1f}C\\0.1}C\n", data.temperature);
    (*display).printf("Humedad: %.1f/\\0.1/\n", data.humidity);
    (*display).printf("Indice de calor: %.2f}C\n", data.heat_index);
    (*display).printf("CO_2: %.0fppm aprox.\n", data.co2);
    (*display).printf("RS: %.3fk", r0);
    
    (*display).display();

}