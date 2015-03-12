# OpenWeatherDuino
Openweathermap + Arduino = OpenWeatherDuino: <br>
An Arduino based standalone Open Source Weather Station which is connected to Openweathermap.org.<br>
This is an very early Version, but it works quite fine and is stable. If you find any bugs, please report them at https://github.com/Benjamin3992/OpenWeatherDuino/issues .<br>
More features will be added in near future, so make sure to check back soon.

# Features
  - Transfering Temperature, Humidity and Location (More will be added soon) via the Openweathermap-API 
  - Uses the inexpensive DHT11/DHT22 for Humidity and Temperature via the arduino-DHT by markruys
  - Two Versions for, Testing (Serial debugging and data will be send) and Deploying (No Serial output)
  - Only ~~20kb~~ 15kb small
  - Sends the data via Ethernet (Wifi is WIP) to the Openweathermap

# Requirements
- All Versions
  - The DHT-libary from https://github.com/markruys/arduino-DHT
  - DHT11 or DHT22 temperature sensor
  - Plastic enclosure
  - Powersupply for the Arduino

- Ethernet version:
  - Any shield-compatible arduino-compatible board with 32kb flash
  - Ethernet shield

- Wifi version(WIP):
  - Any Arduino with more than 16kb flash
  - ESP8266 WIFI Serial Module
# ToDo
  - Adding more sensors
  - Wifi Module (ESP8266)
  - Adding a pressure sensor (maybe BMP180/BMP085)
  - Adding a UV-Index sensor with brightness sensor (maybe Adafruit SI1145)
  - porting the whole API
  - Pictures :D
  - ~~Cleaning up the code~~
  - Creating a logging-to-SD fork
