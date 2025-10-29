// ===== File: input.ino =====
#include "config.h"
#include "pins.h"

extern MenuState currentState;
extern int setTemperature, fanDuration, heatDuration;
extern int menuIndex;
extern const int menuItems;
extern unsigned long lastInputTime;
extern bool systemBusy;

// Flag to toggle between seconds and minutes
bool durationInMinutes = false;
bool tempInTens = false;  // false = step 1°C, true = step 10°C

void handleInput() {
  if (digitalRead(BUTTON_UP) == LOW) {
    systemBusy = true;
    lastInputTime = millis();
    handleUp();
    beepOnButtonPress();   // beep on UP
    delay(200);
    systemBusy = false;
  }
  if (digitalRead(BUTTON_DOWN) == LOW) {
    systemBusy = true;
    lastInputTime = millis();
    handleDown();
    beepOnButtonPress();   // beep on DOWN
    delay(200);
    systemBusy = false;
  }
  if (digitalRead(BUTTON_SELECT) == LOW) {
    systemBusy = true;
    lastInputTime = millis();
    handleSelect();
    beepOnButtonPress();   // beep on SELECT
    delay(200);
    systemBusy = false;
  }
  if (digitalRead(BUTTON_BACK) == LOW) {
    systemBusy = true;
    lastInputTime = millis();
    handleBack();
    beepOnButtonPress();
    delay(200);
    systemBusy = false;
  }
}

void handleUp() {
  systemBusy = true;
  switch (currentState) {
    case MAIN_MENU:
      if (menuIndex > 0) menuIndex--;
      showMainMenu(menuIndex);
      break;

    case SET_TEMP:
      if (tempInTens) {
        setTemperature += 10;
        showSetTemp(setTemperature);
      } else {
        setTemperature += 1;
        showSetTemp(setTemperature);
      }
      break;

    case FAN_DURATION:
      if (durationInMinutes) {
        fanDuration += 60;  // increment by 1 minute
        showFanDuration(fanDuration);
      } else {
        fanDuration += 1;   // increment by 1 second
        showFanDuration(fanDuration);
      }
      break;

    case HEAT_DURATION:
      if (durationInMinutes) {
        heatDuration += 60;
        showHeatDuration(heatDuration);
      } else {
        heatDuration += 1;
        showHeatDuration(heatDuration);
      }
      break;

    case SET_HYSTERESIS:
      if (tempInTens) {
        hysteresis += 10;
        showHysteresis(hysteresis);
      } else {
        hysteresis += 1;
        showHysteresis(hysteresis);
      }
      break;

    default:
      break;
  }
  systemBusy = false;
}

void handleDown() {
  systemBusy = true;
  switch (currentState) {
    case MAIN_MENU:
      if (menuIndex < menuItems - 1) menuIndex++;
      showMainMenu(menuIndex);
      break;

    case SET_TEMP:
      if (tempInTens && setTemperature >= 10) {
        setTemperature -= 10;
        showSetTemp(setTemperature);
      } else if (!tempInTens && setTemperature > 0) {
        setTemperature -= 1;
        showSetTemp(setTemperature);
      }
      break;

    case FAN_DURATION:
      if (durationInMinutes && fanDuration >= 60) {
        fanDuration -= 60;
        showFanDuration(fanDuration);
      } else if (!durationInMinutes && fanDuration > 0) {
        fanDuration -= 1;
        showFanDuration(fanDuration);
      }
      break;

    case HEAT_DURATION:
      if (durationInMinutes && heatDuration >= 60) {
        heatDuration -= 60;
        showHeatDuration(heatDuration);
      } else if (!durationInMinutes && heatDuration > 0) {
        heatDuration -= 1;
        showHeatDuration(heatDuration);
      }
      break;

    case SET_HYSTERESIS:
      if (tempInTens && hysteresis >= 10) {
        hysteresis -= 10;
        showHysteresis(hysteresis);
      } else if (!tempInTens && hysteresis > 0) {
        hysteresis -= 1;
        showHysteresis(hysteresis);
      }
      break;

    default:
      break;
  }
  systemBusy = false;
}

void handleSelect() {
  systemBusy = true;
  switch (currentState) {
    case MAIN_MENU:
      switch (menuIndex) {
        case 0: currentState = SET_TEMP; showSetTemp(setTemperature); break;
        case 1: currentState = FAN_DURATION; showFanDuration(fanDuration); break;
        case 2: currentState = HEAT_DURATION; showHeatDuration(heatDuration); break;
        case 3: currentState = SET_HYSTERESIS; showHysteresis(hysteresis); break;
      }
      break;

    case SET_TEMP:
      // Toggle 1°C / 10°C step mode
      tempInTens = !tempInTens;
      showSetTemp(setTemperature);
      break;

    case FAN_DURATION:
      // Toggle sec/min mode
      durationInMinutes = !durationInMinutes;
      showFanDuration(fanDuration);
      break;

    case HEAT_DURATION:
      // Toggle sec/min mode
      durationInMinutes = !durationInMinutes;
      showHeatDuration(heatDuration);
      break;

    case SET_HYSTERESIS:
      // Toggle 1C / 10C step mode
      tempInTens = !tempInTens;
      showHysteresis(hysteresis);
      break;

    default:
      currentState = MAIN_MENU;
      menuIndex = 0;
      showMainMenu(menuIndex);
      break;
  }
  systemBusy = false;
}

void handleBack() {
  systemBusy = true;

  if (currentState != MAIN_MENU && currentState != IDLE_SCREEN) {
    // Return to menu, keep same index
    currentState = MAIN_MENU;
    showMainMenu(menuIndex);
  } else {
    // Already in main menu — reset to first item
    currentState = MAIN_MENU;
    menuIndex = DEFAULT_MENU_INDEX;
    showMainMenu(menuIndex);
  }
  systemBusy = false;
}

bool anyButtonPressed() {
  return digitalRead(BUTTON_UP) == LOW || 
         digitalRead(BUTTON_DOWN) == LOW ||
         digitalRead(BUTTON_SELECT) == LOW || 
         digitalRead(BUTTON_BACK) == LOW;
}
