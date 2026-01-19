#include <Wire.h>
#include "Adafruit_TCS34725.h"
#define TEMT6000_PIN A0
#define Relay_PIN 15

Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_50MS,
  TCS34725_GAIN_4X
);


/*
Turns the Relay On and OFF according to voltage detected on the photosensor. 
Relay on Pin 15
Photosensor on A0
SDA on 2
SCL on 3
*/

// --- Experiment control ---
bool experimentRunning = false;
unsigned long startTime = 0;

void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println("Initializing...");

  // Initialize TCS34725 color sensor
  if (tcs.begin()) {
    Serial.println("TCS34725 sensor found!");
  } else {
    Serial.println("No TCS34725 found... check wiring!");
    while (1); // Stop if not found
  }

  pinMode(TEMT6000_PIN, INPUT);
    // initialize digital pin LED_BUILTIN as an output.
  pinMode(Relay_PIN, OUTPUT);
  
  Serial.println("Type 'START' to begin experiment, 'STOP' to end.");
  digitalWrite(Relay_PIN, LOW);
}

void loop() {
  // --- Check for serial commands ---
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.equalsIgnoreCase("START")) {
      startExperiment();
    } else if (command.equalsIgnoreCase("STOP")) {
      stopExperiment();
    }
  }

  // --- If experiment running, record data ---
  if (experimentRunning) {
    logData();

    
    if (limitReached()) {
      digitalWrite(15, HIGH);
      stopExperiment();
    }
    delay(1000); // 1 second between readings
  }
}

void startExperiment() {
  if (experimentRunning) {
    Serial.println("Experiment already running.");
    return;
  }

  startTime = millis();
  experimentRunning = true;

  Serial.println("Experiment started. Logging data...");

  Serial.println("Circuit is on.");
  digitalWrite(Relay_PIN, LOW);

  // Print CSV header
  Serial.println("Time (s),Voltage (V),Red,Green,Blue");
}

void stopExperiment() {
  if (!experimentRunning) {
    Serial.println("No experiment running.");
    return;
  }

  experimentRunning = false;
  Serial.println("Experiment stopped.");
}

void logData() {
  float red, green, blue;
  float voltage = getVoltage();
  
  tcs.getRGB(&red, &green, &blue);
  unsigned long elapsed = (millis() - startTime) / 1000; // seconds

  // Print data in CSV format
  Serial.print(elapsed);
  Serial.print(",");
  Serial.print(voltage, 2);
  Serial.print(",");
  Serial.print((int)red);
  Serial.print(",");
  Serial.print((int)green);
  Serial.print(",");
  Serial.println((int)blue);
}

bool limitReached() {
  activationVoltage = 4.0; //Volts
  if (getVoltage() >= activationVoltage;
    return True;
}

void normalizeVoltage() {}
  // Make method to normalize voltage to ambient conditions. Will serve as baseline for determing if reaction has occurred.
}

double getVoltage() {
  int rawValue = analogRead(TEMT6000_PIN);
  float voltage = rawValue * (5.0 / 1023.0);
  return voltage;
}