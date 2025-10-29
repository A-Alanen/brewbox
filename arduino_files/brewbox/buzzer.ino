// ===== File: buzzer.ino =====
#include "config.h"
#include "pins.h"

extern bool safetyLatched;
extern bool systemBusy;

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
  systemBusy = true;
  playTone(BUZZER_DEFAULT_FREQ, 200);
  systemBusy = false;
}

// Two quick peeps for DHT error
void beepError() {
  systemBusy = true;
  playTone(BUZZER_DEFAULT_FREQ, 100);
  delay(100);
  playTone(BUZZER_DEFAULT_FREQ, 100);
  systemBusy = false;
}

// Long low tone for full system shutdown (sensor fail)
void beepShutdown() {
  systemBusy = true;
  playTone(600, 500);  // Lower frequency, longer duration
  delay(100);
  playTone(400, 500);  // Optional second tone for emphasis
  systemBusy = false;
}

// Beep when a button is pressed
void beepOnButtonPress() {
  systemBusy = true;
  playTone(BUZZER_DEFAULT_FREQ, 100); // short 100 ms beep
  systemBusy = false;
}
