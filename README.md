# OpenWeatherDuino
Openweathermap + Arduino = OpenWeatherDuino: <br>
An Arduino based standalone Open Source Weather Station which is connected to Openweathermap.org.<br>
This is an very early Version, but it works quite fine and is stable. If you find any bugs, please report them at https://github.com/Benjamin3992/OpenWeatherDuino/issues .<br>
More features will be added in near future, so make sure to check back soon.

# Features
  - Transfering Temperature, Humidity and Location (More will be added soon) via the Openweathermap-API 
  - Uses the inexpensive DHT11/DHT22 for Humidity and Temperature via the arduino-DHT by markruys
  - Three Versions for ~~Debugging only(Only Serial output no data will be sent)~~, Testing (Serial debugging and data will be send) and Deploying (No Serial output)
  - Only ~~20kb~~ 15kb small
  - Sends the data via Ethernet to the Openweathermap

# Requirements
  - Any shield-compatible arduino-compatible board with 32kb flash
  - The DHT-libary from https://github.com/markruys/arduino-DHT
  - Ethernet sheield (or WiFi shield WIP)
  - DHT11 or DHT22 Temperature sensor
  - Plastic enclosure
  - Powersupply for the Arduino

# ToDo
  - Adding more sensors
  - Adding a pressure sensor (maybe BMP180/BMP085)
  - Adding a UV-Index sensor with brightness sensor (maybe Adafruit SI1145)
  - porting the whole API
  - Pictures :D
  - ~~Cleaning up the code~~
  - Creating a WiFi fork
  - Creating a logging-to-SD fork
