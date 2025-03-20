# wstat (Cheap homemade weather station)

This is a weather station with a HMI vinculated by a socket structure. It measures temperature, humidity, pressure, CO2 in air, wind strength/direction. Developed over ESP32 with [Arduino](https://docs.arduino.cc/) framework. The Desktop software is written in Python, using [Dear PyGui](https://dearpygui.readthedocs.io/en/latest/) package.

## Hardware

### NodeMCU ESP32
### MQ-135
### DHT22
### BMP280
### x3 ≈10nF capacitors
Used to filter the noise from the sensors signal.
### x4 ≈10kΩ 1/4W resistors
Conforming a pull-up with DHT22 and the buttons. It can also be used the internal pull-up directives for the ESP32. `pinMode(pin, INPUT_PULLUP)`
### x3 buttons
Interacting with UI and energy consumption.
### x2 Hall Sensor
### x3 Neodymium magnet
