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

#define server "www.openweathermap.org"  //Do not change!
#define CredBase64 ""  //Enter here the BASE64 encoded Credentials in the form <Username>:<Password>
#define DhtPin 2  //DHT Temperature and Humidity Sensor PIN goes here
#define UploadCycle 10 //Time in minutes between two uploads goes here

const String StationName = "OpenWeatherDuino1";  //Enter the Station Name how it will be displayed on Openweathermap.org
const String lat = "10.0000000";  //Latitude goes here
const String lng = "10.00000000";  //Longitude goes here
const String alt = "0";  //Enter your Altitude in meters without decimals
double doubleAlt = 0.0;  //and here too

byte mac[] = {0x46, 0x46, 0x46, 0x46, 0x46, 0x46};  //Enter a HEX-coded MAC-Adress here
const IPAddress ip(192, 168, 178, 200);  //Enter the IP your Arduino will get here
EthernetClient client;
DHT dht;
SFE_BMP180 pressure;

void setup() {
  dht.setup(DhtPin);
  pressure.startPressure(3);
  pressure.startTemperature();
  Ethernet.begin(mac, ip);
}

void loop() {
  delay(1000);
  double t;
  pressure.getTemperature(t);  //getting the Temperature from the BMP180 Sensor
  t=(9.0/5.0)*t+32.0,2;
  int lenT;
  if (t<-100.00) {lenT=7;}
  else if(t>-100.00&&t<-10.00)  {lenT=6;}
  else if(t>-10.00&&t<0.00)  {lenT=5;}
  else if(t>=0.00&&t<10.00)  {lenT=4;}
  else if(t>=10.00&&t<100.00)  {lenT=5;}
  double p;
  pressure.getPressure(p,doubleAlt);
  int lenP;
  if (p<1000.00)  {lenP=6;}
  else if (p>=1000.00)  {lenP=7;}  
  int h=dht.getHumidity();
  if (client.connect(server, 80)) {  //connecting to the Openweathermap server
    client.println("POST /data/post HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.print("Authorization: Basic ");
    client.println(CredBase64);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(int(floor(log10(abs(h))) + lenT + lenP + StationName.length() + lat.length() + lng.length() + alt.length() + 47));  //Calculating the Length of the Data for the POST method
    client.println();
    client.print("temp=");
    client.print(t);
    client.print("&humidity=");
    client.print(h);
    client.print("&pressure=");
    client.print(p);
    client.print("&lat=");
    client.print(lat);
    client.print("&long=");
    client.print(lng);
    client.print("&alt=");
    client.print(alt);
    client.print("&name=");
    client.print(StationName);
    client.println();
    client.stop();
    for(int i=0; i>=UploadCycle*60; i++)  {
      delay(1000);
    }
  }
}
