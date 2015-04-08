/*
OpenWeatherDuino by Benjamin Ritter
Ver. 1.5
Visit me at Github:
https://github.com/Benjamin3992/OpenWeatherDuino
*/
#include <DHT.h>
#include <SPI.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <SFE_BMP180.h>
#include <Wire.h>
#define server "www.openweathermap.org" //Do not change!
#define CredBase64 "" //Enter here the BASE64 encoded Credentials in the form <Username>:<Password>
#define DhtPin 2 //DHT Temperature and Humidity Sensor PIN goes here
#define UploadCycle 1   //Time in minutes between two uploads goes here
const String StationName = "OpenWeatherDuino1"; //Enter the Station Name how it will be displayed on Openweathermap.org
const String lat = "10.0000000"; //Latitude goes here
const String lng = "10.0000000"; //Longitude goes here
const String alt = "540"; //Enter your Altitude in meters without decimals
double doubleAlt = 540.0; //and here too
byte mac[] = {0x46, 0x46, 0x46, 0x46, 0x46, 0x46}; //Enter a HEX-coded MAC-Adress here
const IPAddress ip(192, 168, 178, 200); //Enter the IP your Arduino will get here
EthernetClient client;
DHT dht;
SFE_BMP180 pressure;


void setup() {
  pressure.begin();
  dht.setup(DhtPin);
  Serial.begin(9600);
}


void loop() {
  char status;
  double t, p;
  status = pressure.startTemperature();
  delay(status);
  pressure.getTemperature(t);
  delay(1000);
  status = pressure.startPressure(3);
  delay(status);
  pressure.getPressure(p, t);
  int lenT;
  if (t < -100.00) {
    lenT = 7;
  }
  else if (t > -100.00 && t <= -10.00) {
    lenT = 6;
  }
  else if (t > -10.00 && t < 0.00) {
    lenT = 5;
  }
  else if (t >= 0.00 && t < 10.00) {
    lenT = 4;
  }
  else if (t >= 10.00 && t < 100.00) {
    lenT = 5;
  }
  int lenP;
  if (p < 1000.00) {
    lenP = 6;
  }
  else if (p >= 1000.00) {
    lenP = 7;
  }
  int h = dht.getHumidity();
  if (client.connect(server, 80)) { //connecting to the Openweathermap server
    Serial.println("POST /data/post HTTP/1.1");
    Serial.print("Host: ");
    Serial.println(server);
    Serial.print("Authorization: Basic ");
    Serial.println(CredBase64);
    Serial.println("Content-Type: application/x-www-form-urlencoded");
    Serial.print("Content-Length: ");
    Serial.println(int(floor(log10(abs(h))) + lenT + lenP + StationName.length() + lat.length() + lng.length() + alt.length() + 47)); //Calculating the Length of the Data for the POST method
    Serial.println();
    Serial.print("temp=");
    Serial.println(t, 2);
    Serial.println(t, 1);
    Serial.println(t, 0);
    Serial.println(t);
    Serial.print("&humidity=");
    Serial.print(h);
    Serial.print("&pressure=");
    Serial.print(p, 2);
    Serial.print("&lat=");
    Serial.print(lat);
    Serial.print("&long=");
    Serial.print(lng);
    Serial.print("&alt=");
    Serial.print(alt);
    Serial.print("&name=");
    Serial.print(StationName);
    Serial.println();
    client.stop();
    delay(60000 * UploadCycle);
  }
}
