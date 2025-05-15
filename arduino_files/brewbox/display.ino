#include <LiquidCrystal.h>

// Reuse the same LCD object as declared in the main file
extern LiquidCrystal lcd;
extern int temperature;

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp set");
  lcd.setCursor(0, 1);
  lcd.print(":");
  lcd.setCursor(4, 1);
  lcd.print(temperature);
  lcd.print((char)223);  // Degree symbol
  lcd.print("C");
}