(currently in development)
# wstat

This is a weather station with a desktop software vinculated by a socket structure. It measures temperature, humidity, pressure, CO2 in air, wind strength/direction. Developed over ESP32 with [Arduino](https://docs.arduino.cc/) framework. The Desktop software is written in Python, using [Dear PyGui](https://dearpygui.readthedocs.io/en/latest/) package.

## Testing/Prototype components

### NodeMCU ESP32
The development board, data processing/sending.
### MQ-135
Measuring CO2 concentration from a known air measure.
### DHT22
Measures temperature and RH in 40 bits sent in series.
### BMP280
Measures pressure and temperature by piezoresistive effect<sup>[1](https://en.m.wikipedia.org/wiki/Piezoresistive_effect)</sup>.
### x6 ≈10nF capacitors
Used to filter<sup>[2](https://en.m.wikipedia.org/wiki/Low-pass_filter)</sup> the noise from the sensors signal/user inputs.
### x4 ≈10kΩ 1/4W resistors
Conforming a pull-up with DHT22 and buttons.
### x1 DISPLAY OLED 1.3' 128x64
To display the measurements from the device itself.
### x4 buttons
Interacting with UI and energy consumption.
### x1 Hall Effect<sup>[3](https://en.m.wikipedia.org/wiki/Hall_effect)</sup> Sensor
For wind strength measurement.
### x3 Neodymium magnet
For wind strength measurement.
