// ===== File: relay.ino =====
#include "config.h"
#include "pins.h"

extern int currentTemp, setTemperature, fanDuration, heatDuration, relayDelay, hysteresis;
extern bool safetyLatched;

unsigned long lastRelayAction = 0;
unsigned long heaterOnSince = 0;
unsigned long fanOnSince = 0;
bool heaterOn = false;
bool fanOn = false;

void updateRelays() {
  unsigned long now = millis();

  // Safety latch: force heater OFF, fan ON
  if (safetyLatched) {
    digitalWrite(RELAY_HEATER, HEATER_OFF);
    digitalWrite(RELAY_FAN, FAN_ON);
    heaterOn = false;
    fanOn = true;
    return;
  }
 // Stop heater after its duration
  if (heaterOn && (now - heaterOnSince >= (unsigned long)heatDuration * 1000UL)) {
    digitalWrite(RELAY_HEATER, HEATER_OFF);
    heaterOn = false;
    lastRelayAction = now;
  }

  // Stop fan after its duration
  if (fanOn && (now - fanOnSince >= (unsigned long)fanDuration * 1000UL)) {
    digitalWrite(RELAY_FAN, FAN_OFF);
    fanOn = false;
    lastRelayAction = now;
  }

  // If idle and relay delay has passed, decide action
  if (!heaterOn && !fanOn && (now - lastRelayAction >= (unsigned long)relayDelay * 1000UL)) {
    if (currentTemp >= setTemperature + hysteresis) {
      // Too hot → start fan cycle
      digitalWrite(RELAY_HEATER, HEATER_OFF);
      digitalWrite(RELAY_FAN, FAN_ON);
      fanOn = true;
      fanOnSince = now;
    } 
    else if (currentTemp <= setTemperature - hysteresis) {
      // Too cold → start heater cycle
      digitalWrite(RELAY_FAN, FAN_OFF);
      digitalWrite(RELAY_HEATER, HEATER_ON);
      heaterOn = true;
      heaterOnSince = now;
    }
  }
}