/*
OpenWeatherDuino by Benjamin Ritter
Ver. 1.5
Visit me at Github:
https://github.com/Benjamin3992/OpenWeatherDuino
*/


#include <DHT.h>
#include <SPI.h>
#include <SFE_BMP180.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#define server "openweathermap.org" //Do not change!
#define CredBase64 "" //Enter here the BASE64 encoded Credentials in the form <Username>:<Password>
#define DhtPin 9 //DHT Temperature and Humidity Sensor PIN goes here
#define UploadCycle 30   //Time in minutes between two uploads goes here (30 minutes is a good idea)
#define SSID "Your Wifi SSID"
#define password "Your Wifi password"


const String StationName = ""; //Enter the Station Name how it will be displayed on Openweathermap.org
const String lat = "10.00000000"; //Latitude goes here
const String lng = "10.00000000"; //Longitude goes here
const String alt = "123"; //Enter your Altitude in meters without decimals

DHT dht;
SFE_BMP180 pressure;
SoftwareSerial ESP8266(10, 11);
//ESP8266-RX --> Arduino Pin 2
//ESP8266-TX --> Arduino Pin 3

void setup() {
  pressure.begin();
  dht.setup(DhtPin);
  ESP8266.begin(9600);
  delay(1000);
}


void loop() {
  connect2Wifi();
  char status;
  double t, p;
  status = pressure.startTemperature();
  delay(status);
  pressure.getTemperature(t);
  status = pressure.startPressure(3);
  delay(status);
  pressure.getPressure(p, t);
  int h = dht.getHumidity();
  String packet = "";
  packet += "temp=";
  packet += (int)t, 2;
  packet += "&humidity=";
  packet += h;
  packet += "&pressure=";
  packet += p, 2;
  packet += "&lat=";
  packet += lat;
  packet += "&long=";
  packet += lng;
  packet += "&alt=";
  packet += alt;
  packet += "&name=";
  packet += StationName;
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += server;
  cmd += "\",80";
  ESP8266.println(cmd);

  while (ESP8266.available()) {
    ESP8266.read(); //clear the incoming buffer
  }
  delay(100);
  

  //Build up POST request
  cmd = "POST /data/post HTTP/1.1\n";
  cmd += "Host: ";
  cmd += server;
  cmd += "\n";
  cmd += "Content-Type: application/x-www-form-urlencoded\n";
  cmd += "Authorization: Basic ";
  cmd += CredBase64;
  cmd += "\n";
  cmd += "Content-Length: ";
  cmd += packet.length();
  cmd += "\n";
  cmd += "Connection: close\n\n";
  cmd += packet;
  cmd += "\r\n\r\n";
  ESP8266.print("AT+CIPSEND=");//Send command for POST request
  while (ESP8266.available()) {
    ESP8266.read(); //clear the incoming buffer
  }
  ESP8266.println(cmd.length());//Send length of POST request
  delay(100); //wait for prompt for request
  if (!ESP8266.find(">")) //Did we find the ">" (prompt for request)?
  {
    ESP8266.println("AT+CIPCLOSE");
    delay(1000);
    return; //we screwed up
  }
  ESP8266.print(cmd); //Things look good, send the POST request
  delay(60000 * UploadCycle);
}

boolean connectWifi() {
  delay(1000);
  ESP8266.println("AT+CWMODE=1");
  delay(500); // wait for the response from the above command before clearing the buffer
  while (ESP8266.available()) {
    ESP8266.read(); //clear the incoming buffer
  }

  //Construct the command to connect to AP
  String cmd = "AT+CWJAP=\"";
  cmd += SSID;
  cmd += "\",\"";
  cmd += password;
  cmd += "\"";

  ESP8266.println(cmd); //Send the command to connect to AP
  delay(5000); //Wait until module has returned response to the above command

  //Check if module replied "OK" (connection successful)
  if (ESP8266.find("OK"))
  {
    return true;
  }
  else
  {
    while (ESP8266.available()) {
      ESP8266.read(); //clear the incoming buffer
    }
    return false;
  }
}

void connect2Wifi() {
  boolean connected = false;
  for (int i = 0; i < 5; i++)
  {
    if (connectWifi())
    {
      connected = true;
      ESP8266.println("AT+CIPMUX=0");
      delay(5000);
      break;
    }
  }
  if (!connected) {
  }
}
