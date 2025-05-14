const int potPin = A0;  // Analog pin A0
int potValue = 0;       // Variable to store potentiometer value
int temperature = 0;    // Variable to store mapped temperature value

void setup() {
    // Start the serial communication at 9600 baudrate
    Serial.begin(9600);
}

void loop() {
  // Read the potentiometer value (0 to 1023)
  potValue = analogRead(potPin);
  
  // Send the potentiometer value to the Serial Monitor
  Serial.print("Potentiometer:");
  Serial.println(potValue);

  // Map the potentiometer value (0-1023) to temperature range (0-150)
  temperature = map(potValue, 0, 1024, 0, 150);
  
  // Send the temperature value to the Serial Monitor
  Serial.print("Temperature:");
  Serial.print(temperature);
  Serial.println("°C");
  
  // Wait for a short time before reading again
  delay(100); // Delay for 100 milliseconds
}
