#include <Encoder.h>

#define Encoder_A 8 
#define Encoder_B 9 
#define Ticks_per_rev 700

int Motor_PWM_Pin=1;  
int Motor_Dir_Pin=0;

// Initialize encoder object
Encoder myEnc(Encoder_A, Encoder_B);

float kp = 1.0;  // Proportional gain
float ki = 0.01; // Integral gain
float kd = 0.1;  // Derivative gain
float time=0.1;

float setSpeed = 100.0; //desired speed of the motor

// Define variables
volatile long prevTicks = 0;  // Previous encoder ticks
unsigned long prevTime = 0;   // Previous time in milliseconds
float currentSpeed = 0;       // Actual motor speed in RPM
float error, integralError = 0.0, lastError = 0.0;
float motorOutput = 0;

void setup() {
    Serial.begin(9600);

    pinMode(Motor_PWM_Pin, OUTPUT);
    pinMode(Motor_Dir_Pin, OUTPUT);

    prevTime = millis();  // Initialize time
}

// Function to calculate motor speed using encoder
float readSpeed() {
    unsigned long currentTime = millis();
    long currentTicks = myEnc.read();  // Read encoder position

    // Calculate RPM
    float tickDifference = currentTicks - prevTicks;
    float timeDifference = (currentTime - prevTime) / 1000.0; // Convert ms to seconds
    float rpm = (tickDifference / Ticks_per_rev) * 60.0 / timeDifference;

    // Update previous values
    prevTicks = currentTicks;
    prevTime = currentTime;

    return rpm;
}

void loop() {
    // Read actual speed from encoder
    currentSpeed = readSpeed();

    // Compute PID error
    error = setSpeed - currentSpeed;
    integralError += error;  // Accumulate error for integral term
    float derivativeError = (error - lastError)/time ;  // Compute derivative term

    // Compute PID output
    motorOutput = (kp * error) + (ki * integralError) + (kd * derivativeError);

    //Ensures motorOutput stays within 0-255, which is the valid range for PWM signals.
    motorOutput = constrain(motorOutput, 0, 255);

    // Send PWM signal to motor
    analogWrite(Motor_PWM_Pin, motorOutput);
    digitalWrite(Motor_Dir_Pin, HIGH);  // Set motor direction

    // Store error for next iteration
    lastError = error;

    // Print speed and PID output
    Serial.print("Set Speed: ");
    Serial.print(setSpeed);
    Serial.print("  Current Speed: ");
    Serial.print(currentSpeed);
    Serial.print("  Output: ");
    Serial.println(motorOutput);

    delay(20);  // Small delay for stability
}
