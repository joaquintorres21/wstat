#include <wstat.h>

#include <display.h>
#include <controller.h>
#include <Wire.h>

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHT 19
#define MQ 36

#define BMP_SDA 21 //I2C comms
#define BMP_CLK 22
#define BMP_ADD 0x76

#define PAGE_CHANGE_BUTTON 25 
#define CHILL_MODE_BUTTON 26

dht_data dht_d;
mq_data mq_d;
bmp_data bmp_d;
bmp_const bmp_param;
float mq_r;
meteor_data packet;

state_t page_s = 0; 
state_t ch_s = 0;
uint8_t page_b = PAGE_CHANGE_BUTTON; 
uint8_t ch_b = CHILL_MODE_BUTTON;

void setup(){

    Wire.begin();
    Serial.begin(115200);
    delay(250);

    pinMode(36, INPUT);
    
    display.begin(SCREEN_ADDRESS, true);
    display.setTextColor(SH110X_WHITE);
    display.setFont(&Org_01);
    display.clearDisplay();

    Wire.beginTransmission(BMP_ADD);
    Wire.write(0xF4);
    Wire.write(0x27);
    Wire.endTransmission();

    bmp_param = bmp_parameters(BMP_ADD);

    
}

void loop() {

    dht_d = dht_get(DHT);
    mq_d = mq_get(MQ,30.0);
    //being 30.0 the result from mq_calibrate(MQ)
    bmp_d = bmp_get((uint16_t)BMP_ADD);
    delay(500);
    bmp_d = bmp_process(bmp_d, bmp_param);

    Serial.printf("T: %d P:%dhPa\n",bmp_d.temperature, bmp_d.pressure);
    packet = construct(dht_d, mq_d, bmp_d);

    interface(display, packet, page_s);
    delay(10000);
    display.clearDisplay();

}

void watch(){

    if(!digitalRead(page_b)) page_s = (page_s+1)%4;
    if(!digitalRead(ch_b)) ch_s = !ch_s;

}