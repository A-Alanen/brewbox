// ===== File: sensor.ino =====
#include "DHT.h"
#include "pins.h"

#define DHTTYPE DHT22

DHT dht(DHT_PIN, DHTTYPE);

int currentTemp;
const int SAFETY_TEMP = 50;

void setupSensor() {
  dht.begin();
}

void readTemperature() {
  float t = dht.readTemperature();   //Celsius
  if (!isnan(t)) {
    currentTemp = (int)round(t);
  } else {
    Serial.println("DHT22 read failed!");
  }
}

bool isOverheated() {
  return currentTemp >= SAFETY_TEMP;
}