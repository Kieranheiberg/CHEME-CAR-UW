#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Create the TCS34725 color sensor object
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// TEMT6000 analog pin
#define TEMT6000_PIN A0

void setup() {
  Serial.begin(9600);
  delay(100);

  // Initialize the TCS34725 sensor
  if (tcs.begin()) {
    Serial.println("TCS34725 sensor found!");
  } else {
    Serial.println("No TCS34725 found... check wiring!");
    while (1); // halt if sensor not found
  }

  pinMode(TEMT6000_PIN, INPUT);
}

void loop() {
  float red, green, blue;
  float voltage;

  // --- Read ambient light sensor (TEMT6000) ---
  int rawValue = analogRead(TEMT6000_PIN);
  voltage = rawValue * (5.0 / 1023.0);  // Convert analog value to voltage

  // --- Read color sensor (TCS34725) ---
  //tcs.setInterrupt(false);  // turn on onboard LED for reading
  //delay(10000);               // small delay for stable reading
  tcs.getRGB(&red, &green, &blue);
  //tcs.setInterrupt(true);   // turn off LED to save power

  Serial.print("R: "); Serial.print((int)red);
  Serial.print("  G: "); Serial.print((int)green);
  Serial.print("  B: "); Serial.print((int)blue);

  // TEMT6000 brightness voltage (Low = darrk, high [5V] = bright)
  Serial.print("  V: ");  Serial.print(voltage, 2);  Serial.println(" V");
  
  Serial.println("-----------------------");
  delay(1000);
}
