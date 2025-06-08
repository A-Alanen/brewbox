// ===== File: relay.ino =====
#define RELAY_FAN     4
#define RELAY_HEATER  5
extern int setTemperature, fanDuration, heatDuration, relayDelay;
unsigned long lastRelayAction = 0;
bool fanOn = false, heaterOn = false;

void updateRelays() {
  if (millis() - lastRelayAction < relayDelay * 1000UL) return;

  if (currentTemp > setTemperature) {
    digitalWrite(RELAY_HEATER, LOW);
    digitalWrite(RELAY_FAN, HIGH);
    fanOn = true; heaterOn = false;
    delay(fanDuration * 1000);
    digitalWrite(RELAY_FAN, LOW);
  } else if (currentTemp < setTemperature) {
    digitalWrite(RELAY_FAN, LOW);
    digitalWrite(RELAY_HEATER, HIGH);
    heaterOn = true; fanOn = false;
    delay(heatDuration * 1000);
    digitalWrite(RELAY_HEATER, LOW);
  }

  lastRelayAction = millis();
}
