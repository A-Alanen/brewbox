// ===== File: brewbox.ino =====
#include <Arduino.h>
#include "config.h"
#include "pins.h"

// Sensor
extern void setupSensor();
extern void readTemperature();
extern bool isOverheated();
extern int currentTemp;

// Display
extern void setupDisplay();
extern void showIdleScreen(int setTemp, int currentTemp);
extern void showMainMenu(int index);
extern void showWarning(int temp);

// Buttons
extern bool anyButtonPressed();
extern void handleInput();

// Relay
extern void updateRelays();

// Buzzer
extern void setupBuzzer();
extern void updateBuzzer();
extern void stopBuzzer();

// Menu state
enum MenuState { MAIN_MENU, SET_TEMP, FAN_DURATION, HEAT_DURATION, SET_DELAY, SET_HYSTERESIS, IDLE_SCREEN };
MenuState currentState = MAIN_MENU;

// Settings
int currentTemp = DEFAULT_SET_TEMPERATURE;
int setTemperature = DEFAULT_SET_TEMPERATURE;
int fanDuration = DEFAULT_FAN_DURATION;
int heatDuration = DEFAULT_HEAT_DURATION;
int relayDelay = DEFAULT_RELAY_DELAY;
int hysteresis = DEFAULT_HYSTERESIS;
int menuIndex = DEFAULT_MENU_INDEX;
const int menuItems = MENU_ITEMS;

// Timing
unsigned long lastInputTime = 0;
unsigned long idleTimeout = IDLE_TIMEOUT;

// Safety
bool safetyLatched = false;

void setup() {
  setupDisplay();
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_BACK, INPUT_PULLUP);
  pinMode(RELAY_FAN, OUTPUT);
  pinMode(RELAY_HEATER, OUTPUT);
  digitalWrite(RELAY_FAN, FAN_OFF);
  digitalWrite(RELAY_HEATER, HEATER_OFF);

  setupBuzzer();
  beepOnStartup();
  setupSensor();
  showMainMenu(menuIndex);
}

void safetyShutdown() {
  safetyLatched = true;
  digitalWrite(RELAY_HEATER, HEATER_OFF);
  digitalWrite(RELAY_FAN, FAN_ON);
  updateBuzzer();
  showWarning(currentTemp);
}

void loop() {
  readTemperature();

  // Safety check
  if (isOverheated() || safetyLatched) {
    safetyShutdown();
    return;
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
    menuIndex = DEFAULT_MENU_INDEX;
    showMainMenu(menuIndex);
    lastInputTime = millis();
    delay(200);
  }
}
