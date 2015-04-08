# OpenWeatherDuino
Openweathermap + Arduino = OpenWeatherDuino: <br>
An Arduino based standalone Open Source Weather Station which is connected to Openweathermap.org.<br>
This is an very early Version, but it works quite fine and is stable. If you find any bugs, please report them at https://github.com/Benjamin3992/OpenWeatherDuino/issues .<br>
More features will be added in near future, so make sure to check back soon.

# Features
  - Transfering Temperature, Humidity and Location (More will be added soon) via the Openweathermap-API 
  - Uses the inexpensive DHT11/DHT22 for Humidity and Temperature via the arduino-DHT by markruys
  - Only 20kb small
  - Sends the data via Ethernet (Wifi is WIP) to the Openweathermap

# Requirements
- All Versions
  - The DHT-libary from https://github.com/markruys/arduino-DHT
  - The BMP180-libary from https://github.com/sparkfun/BMP180_Breakout
  - Arduino with 32kb of flash or more
  - DHT11 or DHT22 temperature sensor
  - The BMP180 pressure sensor
  - Plastic enclosure
  - Power supply for the Arduino
  - TTL logic level shifter

- Ethernet version:
  - Arduino Ethernet shield

- WiFi version:
  - ESP8266 WIFI Serial Module
  - 3.3v power supply (I used a TI LM3940 at my 5v VCC of my Arduino)

# ToDo
  - Adding more sensors
  - ~~Wifi Module (ESP8266)~~
  - Adding a UV-Index sensor with brightness sensor (maybe Adafruit SI1145)
  - porting the whole Openweathermap-API
  - Pictures
  - Creating a logging-to-SD fork
