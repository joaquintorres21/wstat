
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
#define MQ 36
#define BMP_SDA 21 //I2C comms
#define BMP_CLK 22

dht_data dht_d;
mq_data mq_d;
meteor_data data;

float temp, hr, heat_index;
float tt, hh, th;

void setup(){

    Serial.begin(115200);
    delay(250);

    pinMode(36, INPUT);
    
    display.begin(i2c_Address, true);
    display.setTextColor(SH110X_WHITE);
    display.setFont(&Org_01);
    display.clearDisplay();
    
}


void loop() {

    dht_d = dht_get(DHT);
    data = testConstruct(dht_d);
    mq_d = mq_get(MQ);
    Serial.printf("MQ135: %.3f", mq_d);
    Serial.println("");
    interface(&display, data);
    delay(10000);
    display.clearDisplay();

}

