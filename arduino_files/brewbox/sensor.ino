// ===== File: sensor.ino =====
#include "config.h"
#include "pins.h"

// Use the DHT22 type
#define DHTTYPE DHT22

// Declare the DHT object (only once)
DHT dht(DHT_PIN, DHTTYPE);

// Externals from other files
extern LiquidCrystal lcd;
extern void beepError();
extern int currentTemp;
extern MenuState currentState;

void setupSensor() {
  dht.begin();
}

void readTemperature() {
  static bool lastReadFailed = false;
  static unsigned long lastReadTime = 0;
  unsigned long now = millis();

  // Read every 2 seconds
  if (now - lastReadTime < 2000) return;
  lastReadTime = now;

  float t = dht.readTemperature();  // read in Celsius

  if (!isnan(t)) {
    currentTemp = (int)(t + 0.5);

    if (lastReadFailed) {
      lastReadFailed = false;
      showIdleScreen(setTemperature, currentTemp);
    }

    // Only update LCD if we are in the idle screen
    if (currentState == IDLE_SCREEN) {
      lcd.setCursor(0, 1); // bottom/right line
      lcd.print("Now:");
      lcd.print(currentTemp);
      lcd.print((char)223); // ° symbol
      lcd.print("C   ");    // clear leftover chars
    }

  } else {
    if (!lastReadFailed) {
      lcd.setCursor(0, 0);
      lcd.print("Sensor  ");
      lcd.setCursor(0, 1);
      lcd.print("Fail!   ");
      beepError();
      lastReadFailed = true;
    }
  }
}

bool isOverheated() {
  return currentTemp >= SAFETY_TEMP;
}
