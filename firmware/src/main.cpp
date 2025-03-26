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


dht_data dht_d;
mq_data mq_d;
bmp_data bmp_d;
bmp_const bmp_param;
meteor_data data;
//checking r_0
float mq_r;

//Where 0 = Page 1 / 1 = Page 2 / 2 = Settings / -1 = Chill mode
state_t global_state = 0;

char temp_n = 1, temp_p = 1, temp_o = 1;


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
    //mq_r = 21.686;

    mq_r = mq_calibrate(MQ);
    //r_0 esta atado con alambre, aun no lo probe en aire limpio (400ppm de co2). tambien hay q destacar que el mq135 no mide especificamente co2,
    //los sensores de co2 salen bastante mas caros, este mide la concentracion de un gas en funcion de una mezcla
    //dada. entonces si varia la concentracion en el aire de cualquier otro gas presente (ch4, h2, n2) la medida tambien va a cambiar.
    //lo que hago es, en base a una mezcla conocida, medir variaciones de co2 y por regresion formar una curva que represente la variacion
    //de la relacion rs/ro a medida que crece la concentracion de dicho gas
    
    bmp_d = bmp_get((uint16_t)BMP_ADD);

    delay(500);

    bmp_d = bmp_process(bmp_d, bmp_param);

    Serial.printf("T: %d P:%dhPa\n",bmp_d.temperature, bmp_d.pressure);
    mq_d = mq_get(MQ,30.0);
        
    data.co2 = mq_d;
    data = construct(dht_d, mq_d, bmp_d);


    interface(display, data, global_state);
    delay(10000);
    display.clearDisplay();

}