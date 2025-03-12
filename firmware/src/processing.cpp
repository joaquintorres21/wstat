#include "wstat.h"

void interface(Adafruit_SH1106G screen, meteor_data variables){
    
    screen.setTextSize(2);
    screen.println("WSTAT");

    screen.setTextSize(1);
    screen.println("Temperatura:");
    screen.println("Humedad:");
    screen.println("Presión:");
    screen.println("Calidad del aire:");

    delay(250);

}



//meteor_data measurements(uint8_t dht,uint8_t mq,uint8_t bmpd,uint8_t bmpc){
//
//    meteor_data data;
//    dht_data dht_d = {0,0,0.0,0.0};
//
//    float t = dht_d.t;
//    float h = dht_d.h;
//    float th = t * h;
//    float tt = t*t;
//    float hh = h*h;
//    float tth = tt*h;
//    float thh = t*hh;
//    float tthh = tt*hh;
//
//    //Based on empirical equation by USA https://www.wpc.ncep.noaa.gov/html/heatindex_equation.shtml
//    data.heat_index = hic[0] + hic[1]*t 
//    + hic[2]*h + hic[3]*th + hic[4]*tt +
//     hic[5]*hh + hic[6]*tth + hic[7]*thh + hic[8]*tthh; 
//    
//    data.temperature = t;
//    data.humidity = h;
//    //data.pressure = p;
//    //data.air_quality = q;
//
//     return data;
//
//}

void testInterface(Adafruit_SH1106G screen, dht_data data){

    screen.setTextSize(2);
    screen.println("WSTAT");
    screen.setTextSize(1);
    screen.printf("Temperatura: %d", data.z_t);
    screen.printf("\nHumedad: %d", data.z_h);
    delay(250);

}