
#define BLYNK_PRINT Serial

#include "DHT.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define DHTPIN D4 
#define DHTTYPE DHT11
#define sensorPin A0

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "########################";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "#################";
char pass[] = "###";

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  int sensorValue = analogRead(sensorPin);
  float realval = 1000 - sensorValue;
  Blynk.virtualWrite(V7, sensorValue);//876 dry 519 wet
  Blynk.virtualWrite(V8, realval);//120 dry 500 wet
  Blynk.virtualWrite(V9, realval/5);
  Serial.println(realval);
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, 100-h);
  Blynk.virtualWrite(V6, t);
  Anuradha05
}
void setup()
{ digitalWrite(D0,HIGH);
digitalWrite(D1,HIGH);
digitalWrite(D2,HIGH);
digitalWrite(D3,HIGH);
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass, "blynk.iot-cm.com", 8080);   
  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}


void loop()
{
  Blynk.run();
  timer.run();
}
