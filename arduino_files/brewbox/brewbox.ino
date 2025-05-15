#include <Arduino.h>
#include <LiquidCrystal.h>  // Add this to support LCD

// LCD pin configuration (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int potPin = A0;       // Analog pin A0
int potValue = 0;            // Variable to store potentiometer value
int temperature = 0;         // Mapped temperature value
int lastTemperature = 0;     // Previous temperature value

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);         // 16 columns, 2 rows
  lcd.clear();
}

void loop() {
  const int samples = 10;
  long sum = 0;

  for (int i = 0; i < samples; i++) {
    sum += analogRead(potPin);
    delay(2);
  }

  potValue = sum / samples;
  temperature = map(potValue, 0, 1023, 18, 30);

  if (abs(temperature - lastTemperature) >= 1) {
    Serial.print("Temperature:");
    Serial.print(temperature);
    Serial.println("°C");

    lastTemperature = temperature;

    // Call display function
    updateLCD();
  }

  delay(100);
}
