
#include <wstat.h>
#include <display.h>
#include <Wire.h>


Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHT 19
#define MQ 36
#define BMP_SDA 21 //I2C comms
#define BMP_CLK 22

dht_data dht_d;
mq_data mq_d;
meteor_data data;
//checking r_0
float mq_r;


void setup(){

    Serial.begin(115200);
    delay(250);

    pinMode(36, INPUT);
    
    display.begin(SCREEN_ADDRESS, true);
    display.setTextColor(SH110X_WHITE);
    display.setFont(&Org_01);
    display.clearDisplay();
    
}

void loop() {

    dht_d = dht_get(DHT);
    
    mq_r = mq_calibrate(MQ);
    //mq_r = 21.686;

    mq_d = mq_get(MQ,80.0);
    data.co2 = mq_d;

    data = construct(dht_d, mq_d, {dht_d.temperature,0});
    
    Serial.printf("R_0 = %.3fkOhm", mq_r);
    Serial.println("");
    Serial.printf("MQ135: %.3fppm de CO2", mq_d);
    Serial.println("");
    Serial.println("");
    interface(&display, data);
    delay(10000);
    display.clearDisplay();

}

