// ===== File: input.ino =====
#include "config.h"
#include "pins.h"

extern MenuState currentState;
extern int setTemperature, fanDuration, heatDuration, relayDelay;
extern int menuIndex;
extern const int menuItems;
extern unsigned long lastInputTime;

void handleInput() {
  if (digitalRead(BUTTON_UP) == LOW) {
    lastInputTime = millis();
    handleUp();
    beepOnButtonPress();   // beep on UP
    delay(200);
  }
  if (digitalRead(BUTTON_DOWN) == LOW) {
    lastInputTime = millis();
    handleDown();
    beepOnButtonPress();   // beep on DOWN
    delay(200);
  }
  if (digitalRead(BUTTON_SELECT) == LOW) {
    lastInputTime = millis();
    handleSelect();
    beepOnButtonPress();   // beep on SELECT
    delay(200);
  }
  if (digitalRead(BUTTON_BACK) == LOW) {
    lastInputTime = millis();

    if (currentState != MAIN_MENU && currentState != IDLE_SCREEN) {
      // Go back to the menu, but keep the same menuIndex
      currentState = MAIN_MENU;
      showMainMenu(menuIndex);
    } else {
      // If already in MAIN_MENU, just reset to first item
      currentState = MAIN_MENU;
      menuIndex = DEFAULT_MENU_INDEX;
      showMainMenu(menuIndex);
    }

    beepOnButtonPress();
    delay(200);
  }
}

void handleUp() {
  switch (currentState) {
    case MAIN_MENU:
      if (menuIndex > 0) menuIndex--;
      showMainMenu(menuIndex);
      break;
    case SET_TEMP:
      setTemperature++;
      showSetTemp(setTemperature);
      break;
    case FAN_DURATION:
      fanDuration++;
      showFanDuration(fanDuration);
      break;
    case HEAT_DURATION:
      heatDuration++;
      showHeatDuration(heatDuration);
      break;
    case SET_DELAY:
      relayDelay++;
      showDelay(relayDelay);
      break;
    case SET_HYSTERESIS:
      hysteresis++;
      showHysteresis(hysteresis);
      break;
    default: break;
  }
}

void handleDown() {
  switch (currentState) {
    case MAIN_MENU:
      if (menuIndex < menuItems - 1) menuIndex++;
      showMainMenu(menuIndex);
      break;
    case SET_TEMP:
      if (setTemperature > 0) setTemperature--;
      showSetTemp(setTemperature);
      break;
    case FAN_DURATION:
      if (fanDuration > 0) fanDuration--;
      showFanDuration(fanDuration);
      break;
    case HEAT_DURATION:
      if (heatDuration > 0) heatDuration--;
      showHeatDuration(heatDuration);
      break;
    case SET_DELAY:
      if (relayDelay > 0) relayDelay--;
      showDelay(relayDelay);
      break;
    case SET_HYSTERESIS:
      if (hysteresis > 0) hysteresis--;
      showHysteresis(hysteresis);
      break;
    default: break;
  }
}

void handleSelect() {
  switch (currentState) {
    case MAIN_MENU:
      switch (menuIndex) {
        case 0: currentState = SET_TEMP; showSetTemp(setTemperature); break;
        case 1: currentState = FAN_DURATION; showFanDuration(fanDuration); break;
        case 2: currentState = HEAT_DURATION; showHeatDuration(heatDuration); break;
        case 3: currentState = SET_DELAY; showDelay(relayDelay); break;
        case 4: currentState = SET_HYSTERESIS; showHysteresis(hysteresis); break;
      }
      break;
    default:
      currentState = MAIN_MENU;
      menuIndex = 0;
      showMainMenu(menuIndex);
      break;
  }
}

bool anyButtonPressed() {
  return digitalRead(BUTTON_UP) == LOW || 
         digitalRead(BUTTON_DOWN) == LOW ||
         digitalRead(BUTTON_SELECT) == LOW || 
         digitalRead(BUTTON_BACK) == LOW;
}
