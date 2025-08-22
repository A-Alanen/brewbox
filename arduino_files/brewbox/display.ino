// ===== File: display.ino =====
#include "pins.h"
#include <LiquidCrystal.h>

extern int currentTemp;

LiquidCrystal lcd(LCD_7, LCD_8, LCD_9, LCD_10, LCD_11, LCD_12);

void setupDisplay() {
  lcd.begin(16, 2);
  lcd.clear();
}

void printTwoLines(const char* line1, const char* line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  for (int i = 0; i < 8 && line1[i] != '\0'; i++) {
    lcd.print(line1[i]);
  }
  lcd.setCursor(0, 1);
  for (int i = 0; i < 8 && line2[i] != '\0'; i++) {
    lcd.print(line2[i]);
  }
}

void showMainMenu(int index) {
  switch (index) {
    case 0: printTwoLines(">SetTemp", "        "); break;
    case 1: printTwoLines(">FanTime", "        "); break;
    case 2: printTwoLines(">HeatDur", "        "); break;
    case 3: printTwoLines(">Delay", "        "); break;
  }
}

void showSetTemp(int temp) {
  char line1[9], line2[9];
  snprintf(line1, 9, "SetTemp:");
  snprintf(line2, 9, "%2d%cC    ", temp, 223);  // 223 is ° symbol
  printTwoLines(line1, line2);
}

void showFanDuration(int seconds) {
  char line1[9], line2[9];
  snprintf(line1, 9, "FanTime:");
  snprintf(line2, 9, "%2ds     ", seconds);
  printTwoLines(line1, line2);
}

void showHeatDuration(int seconds) {
  char line1[9], line2[9];
  snprintf(line1, 9, "HeatTime:");
  snprintf(line2, 9, "%2ds     ", seconds);
  printTwoLines(line1, line2);
}

void showDelay(int seconds) {
  char line1[9], line2[9];
  snprintf(line1, 9, "Delay:");
  snprintf(line2, 9, "%2ds     ", seconds);
  printTwoLines(line1, line2);
}

void showIdleScreen(int setTemp, int currentTemp) {
  char line1[9], line2[9];
  snprintf(line1, 9, "Set:%2d%cC", setTemp, 223);
  snprintf(line2, 9, "Now:%2d%cC", currentTemp, 223);
  printTwoLines(line1, line2);
}

void showWarning(int temp) {
  char line1[9], line2[9];
  snprintf(line1, 9, "WARNING!");
  snprintf(line2, 9, "%2d%cC", temp, 223);
  printTwoLines(line1, line2);
}

void testLcdZones() {
  lcd.clear();
  lcd.setCursor(0, 0);
  for (int i = 0; i < 8; i++) lcd.print(i);
  lcd.setCursor(0, 1);
  for (int i = 0; i < 8; i++) lcd.print(i);
}
