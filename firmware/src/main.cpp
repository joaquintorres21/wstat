
#include "wstat.h"



#define i2c_Address 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

#define DHT 19
#define MQ 10
#define BMP_SDA 21 //I2C comms
#define BMP_CLK 22

dht_data data;

float temp, hr, heat_index;
float tt, hh, th;

void setup(){

    Serial.begin(115200);
    delay(250); // wait for the OLED to power up
    display.begin(i2c_Address, true); // Address 0x3C default
    //display.setContrast (0); // dim display
    display.setTextColor(SH110X_WHITE);
    display.setFont(&Org_01);
    display.clearDisplay();
    
}


void loop() {

    display.clearDisplay();
    //meteor_data weather = measurements(DHT, MQ, BMP_SDA, BMP_CLK);
    display.setCursor(0,10);

    display.setTextSize(2);
    display.println("# WSTAT #");
    data = dht_get(DHT);
    Serial.println("");
    
    display.setTextSize(1);

    temp = data.t / 10.0;
    hr = data.h / 10.0;

    tt = temp*temp;
    hh = hr*hr;
    th = temp*hr;

    display.printf("Temperatura: %.2f}C", temp);
    display.println("");
    display.printf("Humedad relativa: %.2f/", hr);
    display.println("");

    heat_index = hic[0] + hic[1]*temp + hic[2]*hr + hic[3]*th+ hic[4]*tt + hic[5]*hh + hic[6]*tt*hr + hic[7]*temp*hh + hic[8]*tt*hh; 

    display.printf("Indice de calor: %.2f}C", heat_index);
    
    
    display.display();

    delay(10000);

}

