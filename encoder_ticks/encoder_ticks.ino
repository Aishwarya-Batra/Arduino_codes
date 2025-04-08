#include <Encoder.h>

#define ENCODER_PIN_A 10 
#define ENCODER_PIN_B 11 
#define PULSES_PER_REV 700  
// #define motorpwm 10
// #define motordir 9

Encoder myEnc(ENCODER_PIN_A, ENCODER_PIN_B);

volatile long prevTicks = 0;
unsigned long prevTime = 0;
float rpm = 0;

void setup() {
    Serial.begin(9600);
    prevTime = millis();  // Store initial time
}

void loop() {
    unsigned long currentTime = millis();
    long currentTicks = myEnc.read();

    // Calculate RPM every 100ms (0.1 sec)
    if (currentTime - prevTime >= 100) {
        long tickDifference = currentTicks - prevTicks;
        rpm = (tickDifference / (float)PULSES_PER_REV) * 600.0;  // Convert to RPM

        Serial.print("RPM: ");
        Serial.println(rpm);

        prevTicks = currentTicks;
        prevTime = currentTime;
    }
}
