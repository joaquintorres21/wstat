# wstat (Cheap homemade weather station)

This is a weather station with a HMI vinculated by a socket structure. It measures temperature, humidity, pressure, CO2 in air, wind strength/direction. Developed over ESP32 with [Arduino](https://docs.arduino.cc/) framework. The Desktop software is written in Python, using [Dear PyGui](https://dearpygui.readthedocs.io/en/latest/) package.

## Hardware

### NodeMCU ESP32
### MQ-135
Measuring CO2 concentration from a known air measure.
### DHT22
Measures temperature and RH in 40 bits sent in series.
### BMP280
Measures pressure and temperature in a high resolution (20 bits ADC)
### x3 ≈10nF capacitors
Used to filter the noise from the sensors signal.
### x4 ≈10kΩ 1/4W resistors
Conforming a pull-up with DHT22 and the buttons. It can also be used the internal pull-up directives for the ESP32. `pinMode(pin, INPUT_PULLUP)`
### x1 DISPLAY OLED 1.3' 128x64
To display the measurements from the device itself.
### x3 buttons
Interacting with UI and energy consumption.
### x2 Hall Sensor
### x3 Neodymium magnet
