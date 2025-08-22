// ===== File: brewbox.ino =====
#include <Arduino.h>
#include "pins.h"
// External functions and variables
extern void setupSensor();
extern void setupDisplay();
extern void showIdleScreen(int setTemp, int currentTemp);
extern void showMainMenu(int index);
extern void testLcdZones();
extern void updateRelays();
extern void handleInput();
extern void showWarning(int temp);
extern void readTemperature();
extern bool isOverheated();
extern bool anyButtonPressed();
extern int currentTemp;

// Buzzer functions
extern void setupBuzzer();
extern void updateBuzzer();
extern void stopBuzzer();

// Menu state enum
enum MenuState {
  MAIN_MENU,
  SET_TEMP,
  FAN_DURATION,
  HEAT_DURATION,
  SET_DELAY,
  IDLE_SCREEN
};

MenuState currentState = MAIN_MENU;
unsigned long lastInputTime = 0;
const unsigned long IDLE_TIMEOUT = 10000UL;

// Settings
int setTemperature = 25;
int fanDuration = 5;
int heatDuration = 5;
int relayDelay = 10;
int menuIndex = 0;
const int menuItems = 4;

bool safetyLatched = false;

void setup() {
  setupDisplay();
  testLcdZones();
  while (false);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_BACK, INPUT_PULLUP);
  pinMode(RELAY_FAN, OUTPUT);
  pinMode(RELAY_HEATER, OUTPUT);
  digitalWrite(RELAY_FAN, LOW);
  digitalWrite(RELAY_HEATER, LOW);

  setupBuzzer();
  setupSensor();
  showMainMenu(menuIndex);
}

void safetyShutdown() {
  safetyLatched = true;

  // Force heater off, fan on
  digitalWrite(RELAY_HEATER, LOW);
  digitalWrite(RELAY_FAN, HIGH);

  // Buzzer & LCD warning
  updateBuzzer();
  showWarning(currentTemp);
}

void loop() {
  // update currentTemp from sensor
  readTemperature();

  // Safety check
  if (isOverheated() || safetyLatched) {
    safetyShutdown();   // latched mode
    return;             // skip rest of loop
  }

  handleInput();
  updateRelays();
  stopBuzzer();

  if (millis() - lastInputTime > IDLE_TIMEOUT && currentState != IDLE_SCREEN) {
    currentState = IDLE_SCREEN;
    showIdleScreen(setTemperature, currentTemp);
  }

  if (currentState == IDLE_SCREEN && anyButtonPressed()) {
    currentState = MAIN_MENU;
    menuIndex = 0;
    showMainMenu(menuIndex);
    lastInputTime = millis();
    delay(200);
  }
}
