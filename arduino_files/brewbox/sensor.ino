// ===== File: sensor.ino =====
#include "config.h"
#include "pins.h"

// Use the DHT22 type
#define DHTTYPE DHT22

// Declare the DHT object (only once)
DHT dht(DHT_PIN, DHTTYPE);

// Externals from other files
extern bool systemBusy;
extern LiquidCrystal lcd;
extern void beepError();
extern void beepShutdown();
extern int currentTemp;
extern MenuState currentState;

// Safety tracking for sensor failure
static unsigned long sensorFailStart = 0;
bool sensorFailActive = false;
const unsigned long SENSOR_FAIL_TIMEOUT = 30000UL; // 30 seconds

void setupSensor() {
  dht.begin();
}

void readTemperature() {
  if (systemBusy) return;
  
  static bool lastReadFailed = false;
  static unsigned long lastReadTime = 0;
  static float lastGoodTemp = DEFAULT_SET_TEMPERATURE;
  unsigned long now = millis();

  // Read every 3 seconds
  if (now - lastReadTime < 3000) return;
  lastReadTime = now;

  float t = dht.readTemperature();  // read in Celsius

  if (!isnan(t)) {
    currentTemp = (int)(t + 0.5);

    // --- Sensor recovered ---
    if (sensorFailActive) {
      sensorFailActive = false;
      sensorFailStart = 0;      // reset failure timer
      lastReadFailed = false;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sensor");
      lcd.setCursor(0,1);
      lcd.print("OK");
      delay(1000);
      showIdleScreen(setTemperature, currentTemp);
    }

    // Update screen if in idle
    if (currentState == IDLE_SCREEN) {
      lcd.setCursor(0, 1); // bottom line
      lcd.print("Now:");
      lcd.print(currentTemp);
      lcd.print((char)223); // ° symbol
      lcd.print("C   ");
    }

  } else {
    // --- Failed reading ---
    if (!lastReadFailed) {
      lastReadFailed = true;
      sensorFailStart = now; // start timing failure
    }

    // Display fail message
    lcd.setCursor(0, 0);
    lcd.print("Sensor  ");
    lcd.setCursor(0, 1);
    lcd.print("Fail!   ");
    beepError();

    // If failed for more than 30 sec, activate safety
    if (!sensorFailActive && (now - sensorFailStart >= SENSOR_FAIL_TIMEOUT)) {
      sensorFailActive = true;
      digitalWrite(RELAY_HEATER, HEATER_OFF);
      digitalWrite(RELAY_FAN, FAN_OFF);
      lcd.clear();
      lcd.print("Relays  ");
      lcd.setCursor(0, 1);
      lcd.print("off     ");
      beepShutdown();
      // Try to recover the sensor by reinitializing
      dht.begin();  // Reinit the DHT22 to clear hang state
    }
  }
}

bool isOverheated() {
  return currentTemp >= SAFETY_TEMP;
}
