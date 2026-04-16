#include <Servo.h>

Servo servoKI;
Servo servoHCl;

// Component pins
#define Photosensor_PIN A3
#define Relay_PIN 15
#define Rear_Button_PIN 2
#define Servo1_PIN 7
#define Servo2_PIN 9

// Global variables
volatile bool buttonFlag = false;
unsigned long lastMillis = 0;
unsigned long lastMillisPhoto = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 8000;
bool relayON = false;
bool isRunning = false;
double Voltage = 0;

// Rolling average buffer
const int V_BUFFER_SIZE = 10;
double voltageBuffer[V_BUFFER_SIZE] = {0};
int bufferIndex = 0;
bool bufferFull = false;

void setup() {
  Serial.begin(9600);

  servoKI.attach(Servo1_PIN);
  servoKI.write(0);
  servoHCl.attach(Servo2_PIN);
  servoHCl.write(0);
  delay(1000);

  pinMode(Photosensor_PIN, INPUT);
  pinMode(Relay_PIN, OUTPUT);
  pinMode(Rear_Button_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(Rear_Button_PIN), buttonPressed, FALLING);
  digitalWrite(Relay_PIN, LOW);
}

void loop() {
  if (buttonFlag) {
    buttonFlag = false;

    if (!isRunning && millis() - lastDebounceTime > debounceDelay) {
      lastDebounceTime = millis();
      isRunning = true;
      Serial.println("Button pressed");
      digitalWrite(Relay_PIN, LOW);
      moveServos();
      digitalWrite(Relay_PIN, HIGH);
      isRunning = false;
    }
  }

  // Sample voltage every 100ms so buffer fills with 10 readings over ~1s
  if (millis() - lastMillisPhoto >= 100) {
    lastMillisPhoto = millis();
    Voltage = getVoltage();

    // Store in circular buffer
    voltageBuffer[bufferIndex] = Voltage;
    bufferIndex = (bufferIndex + 1) % V_BUFFER_SIZE;
    if (bufferIndex == 0) bufferFull = true;

    // Only evaluate average once buffer has a full 10-sample window
    if (bufferFull) {
      double avgV = getAverageVoltage();

      Serial.print("Voltage: ");
      Serial.print(Voltage);
      Serial.print("  |  Avg (10 samples): ");
      Serial.println(avgV);

      if (limitReached(avgV)) {
        digitalWrite(Relay_PIN, LOW);
      }
    }
  }
}

void buttonPressed() {
  buttonFlag = true;
}

// Compute average of the rolling buffer
double getAverageVoltage() {
  double sum = 0;
  for (int i = 0; i < V_BUFFER_SIZE; i++) {
    sum += voltageBuffer[i];
  }
  double avgV = sum / V_BUFFER_SIZE;
  return avgV;
}

// Now accepts the pre-computed average instead of re-sampling
bool limitReached(double avgV) {
  float activationVoltage = 0.1;
  if (avgV <= activationVoltage) {
    Serial.println("Limit breached");
    return true;
  }
  return false;
}

void normalizeVoltage() {
  // Normalize voltage to ambient conditions as baseline
}

double getVoltage() {
  int rawValue = analogRead(Photosensor_PIN);
  float voltage = rawValue * (5.0 / 1023.0);
  return voltage;
}

void moveServos() {
  servoKI.attach(Servo1_PIN);
  servoHCl.attach(Servo2_PIN);

  servoHCl.write(175);
  delay(1300);
  servoHCl.write(0);
  delay(1000);
  servoKI.write(175);
  delay(1300);
  servoKI.write(0);
  delay(500);

  servoKI.detach();
  servoHCl.detach();
}