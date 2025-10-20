// ===== File: buzzer.ino =====
#include "config.h"
#include "pins.h"

extern bool safetyLatched;

// Setup buzzer pin
void setupBuzzer() {
  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);  // ensure buzzer off
}

// Play a single tone for given duration (ms)
void playTone(int frequency, int duration) {
  tone(BUZZER_PIN, frequency, duration);
  delay(duration + 20); // ensure note finishes
}

// Update buzzer during safety alarm
void updateBuzzer() {
  static unsigned long lastToggle = 0;
  static bool buzzerState = false;
  unsigned long now = millis();

  if (!safetyLatched) {
    noTone(BUZZER_PIN);
    return;
  }

  // Toggle buzzer every 1 second
  if (now - lastToggle >= 1000) {
    buzzerState = !buzzerState;
    if (buzzerState) {
      tone(BUZZER_PIN, BUZZER_DEFAULT_FREQ);
    } else {
      noTone(BUZZER_PIN);
    }
    lastToggle = now;
  }
}

// Stop the buzzer
void stopBuzzer() {
  noTone(BUZZER_PIN);
}

// Beep once at startup
void beepOnStartup() {
  playTone(BUZZER_DEFAULT_FREQ, 200);
}

// Two quick peeps for DHT error
void beepError() {
  playTone(BUZZER_DEFAULT_FREQ, 100);
  delay(100);
  playTone(BUZZER_DEFAULT_FREQ, 100);
}

// Long low tone for full system shutdown (sensor fail)
void beepShutdown() {
  playTone(600, 500);  // Lower frequency, longer duration
  delay(100);
  playTone(400, 500);  // Optional second tone for emphasis
}

// Beep when a button is pressed
void beepOnButtonPress() {
  playTone(BUZZER_DEFAULT_FREQ, 100); // short 100 ms beep
}
