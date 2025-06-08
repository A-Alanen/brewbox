// ===== File: input.ino =====
extern MenuState currentState;
extern int setTemperature, fanDuration, heatDuration, relayDelay;
extern int menuIndex;
extern const int menuItems;
extern unsigned long lastInputTime;

void handleInput() {
  if (digitalRead(BUTTON_UP) == LOW) {
    lastInputTime = millis();
    handleUp();
    delay(200);
  }
  if (digitalRead(BUTTON_DOWN) == LOW) {
    lastInputTime = millis();
    handleDown();
    delay(200);
  }
  if (digitalRead(BUTTON_SELECT) == LOW) {
    lastInputTime = millis();
    handleSelect();
    delay(200);
  }
  if (digitalRead(BUTTON_BACK) == LOW) {
    lastInputTime = millis();
    currentState = MAIN_MENU;
    menuIndex = 0;
    showMainMenu(menuIndex);
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
  return digitalRead(BUTTON_UP) == LOW || digitalRead(BUTTON_DOWN) == LOW ||
         digitalRead(BUTTON_SELECT) == LOW || digitalRead(BUTTON_BACK) == LOW;
}
