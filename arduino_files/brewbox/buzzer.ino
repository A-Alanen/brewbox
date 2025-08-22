// ===== File: buzzer.ino =====
#include "pins.h"

extern bool safetyLatched;

void setupBuzzer() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
}

void updateBuzzer() {
  if (!safetyLatched) {
    digitalWrite(BUZZER_PIN, LOW);
    return;
  }

  // Toggle buzzer every 1 second
  static unsigned long lastToggle = 0;
  static bool buzzerOn = false;

  if (millis() - lastToggle >= 1000) {
    buzzerOn = !buzzerOn;
    digitalWrite(BUZZER_PIN, buzzerOn ? HIGH : LOW);
    lastToggle = millis();
  }
}

void stopBuzzer() {
  digitalWrite(BUZZER_PIN, LOW);
}
