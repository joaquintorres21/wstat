#include "wstat.h"

meteor_data construct(dht_data dht_data, mq_data mq_data, bmp_data bmp_data){
    
    meteor_data measurements;
    
    float tt = bmp_data.temperature*bmp_data.temperature;
    float hh = dht_data.humidity*dht_data.humidity;
    float th = bmp_data.temperature*dht_data.humidity;

    measurements.temperature = bmp_data.temperature;
    measurements.humidity = dht_data.humidity / 10.0;

    measurements.heat_index = hic[0] + hic[1]*measurements.temperature + hic[2]*measurements.humidity + hic[3]*th+ 
    hic[4]*tt + hic[5]*hh + hic[6]*tt*measurements.humidity + hic[7]*measurements.temperature*hh + hic[8]*tt*hh; 
    
    measurements.pressure = bmp_data.pressure;
    measurements.air_quality = mq_data;

    return measurements;
    
}

meteor_data testConstruct(dht_data dht_data){
    
    meteor_data measurements;

    measurements.humidity = dht_data.humidity / 10.0;
    measurements.temperature = dht_data.temperature / 10.0;

    float tt = measurements.temperature*measurements.temperature;
    float hh = measurements.humidity*measurements.humidity;
    float th = measurements.temperature*measurements.humidity;

    measurements.heat_index = hic[0] + hic[1]*measurements.temperature + hic[2]*measurements.humidity + hic[3]*th+ 
    hic[4]*tt + hic[5]*hh + hic[6]*tt*measurements.humidity + hic[7]*measurements.temperature*hh + hic[8]*tt*hh; 
    
    return measurements;
}

void interface(Adafruit_SH1106G* display, meteor_data data){
    
    (*display).setCursor(0,10);

    (*display).setTextSize(2);
    (*display).println("# WSTAT #");

    (*display).setTextSize(1);
    (*display).printf("Temperatura: %.1f}C\\0.1}C", data.temperature);
    (*display).println("");
    (*display).printf("Humedad: %.1f/\\0.1/", data.humidity);
    (*display).println("");
    (*display).printf("Indice de calor: %.2f}C", data.heat_index);
    
    (*display).display();

}