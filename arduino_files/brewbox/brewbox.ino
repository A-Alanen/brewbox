// ===== File: brewbox.ino =====
#include <Arduino.h>

// External functions and variables
extern void setupDisplay();
extern void showIdleScreen(int setTemp, int currentTemp);
extern void showMainMenu(int index);
extern void testLcdZones();
extern void updateRelays();
extern void handleInput();
extern bool anyButtonPressed();
extern int currentTemp;

// Button pins
#define BUTTON_UP     A0
#define BUTTON_DOWN   A1
#define BUTTON_SELECT A2
#define BUTTON_BACK   A3

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

void setup() {
  setupDisplay();
  testLcdZones();
  while (false);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_BACK, INPUT_PULLUP);
  showMainMenu(menuIndex);
}

void loop() {
  // update currentTemp from sensor
  readTemperature();

  handleInput();
  updateRelays();

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
