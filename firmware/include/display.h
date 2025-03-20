/*This header is used by the display to show the sensors information.*/

#include <wtypes.h>

//Adafruit drivers for OLED 1.3' 128x64
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#include <Org_01.h>

#define SCREEN_ADDRESS 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1


void build(Adafruit_SH1106G*, GFXfont*, int color);

//Writes data in the pointed display.
void interface(Adafruit_SH1106G&, meteor_data, state_t);

//Writes the current page based on the state variable. Called during interface(...)
void write_page(Adafruit_SH1106G&, meteor_data, state_t);

