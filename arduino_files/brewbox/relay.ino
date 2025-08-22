// ===== File: relay.ino =====
#include "pins.h"

extern int currentTemp, setTemperature, fanDuration, heatDuration, relayDelay;
unsigned long lastRelayAction = 0;
extern bool safetyLatched;

void updateRelays() {
  if (safetyLatched) {
    digitalWrite(RELAY_HEATER, LOW);
    digitalWrite(RELAY_FAN, HIGH);
    return;
  }
  
  if (millis() - lastRelayAction < relayDelay * 1000UL) return;

  if (currentTemp > setTemperature) {
    digitalWrite(RELAY_HEATER, LOW);
    digitalWrite(RELAY_FAN, HIGH);
    delay(fanDuration * 1000);
    digitalWrite(RELAY_FAN, LOW);
  } else if (currentTemp < setTemperature) {
    digitalWrite(RELAY_FAN, LOW);
    digitalWrite(RELAY_HEATER, HIGH);
    delay(heatDuration * 1000);
    digitalWrite(RELAY_HEATER, LOW);
  }

  lastRelayAction = millis();
}
