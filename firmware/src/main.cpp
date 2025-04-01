#include <wstat.h>

#include <display.h>
#include <controller.h>
#include <Wire.h>
#include <Wifi.h>

WiFiServer Server(2112);
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
uint16_t mq_tr;
meteor_data packet;
int concurrence = 10;

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

    wifi_setup("WSTAT", "wstatAccess");

    attachInterrupt(page_b, switch_page, LOW);
    attachInterrupt(ch_b, switch_chill, LOW);
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

    interface(display, packet, page_s, ch_s);
    delay(100*concurrence);
    display.clearDisplay();

    WiFiClient receiver = Server.available();
    if(receiver){

        Server.write(dht_d.humidity >> 8);
        Server.write(dht_d.humidity);

        delay(100);

        mq_tr = (uint16_t)((mq_d-(int)mq_d)*10);
        Server.write((int)mq_d);
        Server.write(mq_tr >> 8);
        Server.write(mq_tr);
        delay(100);

        Server.write(bmp_d.pressure >> 24);
        Server.write(bmp_d.pressure >> 16);
        Server.write(bmp_d.pressure >> 8);
        Server.write(bmp_d.pressure);

        delay(100);

        Server.write(bmp_d.temperature >> 24);
        Server.write(bmp_d.temperature >> 16);
        Server.write(bmp_d.temperature >> 8);
        Server.write(bmp_d.temperature);
    }

}

void switch_chill(){
    ch_s = !ch_s;
    concurrence = ch_s ? 30 : 10;
    interface(display, packet, page_s, ch_s);
}

void switch_page(){
    page_s = (page_s+1)%4;
    interface(display, packet, page_s, ch_s);
}

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

uint8_t wifi_setup(char* ssid, char* wpa){
    
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, wpa);
    uint64_t t0 = esp_timer_get_time();
    while(WiFi.status() != WL_CONNECTED){
        if(esp_timer_get_time()-t0 > 15E6) return WiFi.status();
    };
    return 0;

}