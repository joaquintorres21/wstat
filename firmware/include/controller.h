/*This header contains all the required functions to control the UI, energy use and WiFi transmitting
in the project. */

#include <wtypes.h>

state_t next(state_t*global,uint8_t button);
state_t prev(state_t*global,uint8_t button);
state_t chill(state_t*global,uint8_t button);

