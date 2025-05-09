(currently in development)
# wstat

This is a weather station that sends data to my PC. It measures temperature, humidity, pressure, CO2 in air, wind strength/direction. Developed over ESP32 with [Arduino](https://docs.arduino.cc/) framework.

## Testing/Prototype components

### NodeMCU ESP32
The development board, data processing/sending.
### MQ-135
Measuring CO2 concentration from a known air measure.
### DHT22
Measures temperature and RH in 40 bits sent in series.
### BMP280
Measures pressure and temperature by piezoresistive effect.
### x3 Neodymium magnet
For wind strength measurement.
### x1 Hall Effect Sensor
For wind strength measurement.
### x5 ≈10nF capacitors
Used to [filter](https://en.m.wikipedia.org/wiki/Low-pass_filter) the noise from the sensors signal/user inputs.
### x4 ≈10kΩ 1/4W resistors
Conforming a pull-up with DHT22 and buttons.
### x1 DISPLAY OLED 1.3' 128x64
To display the measurements from the device itself.
### x2 buttons
Interacting with UI and energy consumption.
