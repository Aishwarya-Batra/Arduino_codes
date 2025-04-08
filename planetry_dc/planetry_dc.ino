// Example code to run a planetary DC motor using an Arduino with an L298N motor driver

#include <Stepper.h>

// Define motor pins connected to L298N
const int motorPin1 = 8;  // Input 1 for motor 1
const int motorPin2 = 9;  // Input 2 for motor 1 
const int motorEnable = 10; // Enable pin for motor 1

void setup() {
  // Set motor pins as outputs
  pinMode(motorPin1, OUTPUT); 
  pinMode(motorPin2, OUTPUT); 
  pinMode(motorEnable, OUTPUT); 
}

void loop() {
  // Run motor forward
  digitalWrite(motorPin1, HIGH); 
  digitalWrite(motorPin2, LOW); 
  analogWrite(motorEnable, 255); // Adjust speed with PWM value (0-255)

  // Optional delay for demonstration
  delay(2000); 

  // Run motor backward
  digitalWrite(motorPin1, LOW); 
  digitalWrite(motorPin2, HIGH);
  analogWrite(motorEnable, 255); 

  // Optional delay for demonstration
  delay(2000); 
}
