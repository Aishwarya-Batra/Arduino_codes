#include <Encoder.h>

#define Encoder_A 9
#define Encoder_B 8 
#define Ticks_per_rev 701 

int Motor_pwm_pin=1; 
int Motor_dir_pin=0; 

Encoder myEnc(Encoder_A, Encoder_B);

volatile long prevTicks = 0;
unsigned long prevTime = 0;
float rpm = 0;
int pwmValue ;  

void setup() {
    Serial.begin(9600);
    
    // pinMode(Encoder_A, INPUT_PULLUP);
    // pinMode(Encoder_B, INPUT_PULLUP);

    pinMode(13,OUTPUT);
    digitalWrite(13,HIGH);
    
    pinMode(Motor_pwm_pin, OUTPUT);
    pinMode(Motor_dir_pin, OUTPUT);
    
    prevTime = millis();  // stores initial time
}

void loop() {

  if (Serial.available() > 0) {  // Check if data is available
        String input = Serial.readStringUntil('\n'); 
        input.trim();  
        pwmValue = input.toInt(); 

        //Serial.print("Received value: ");
        analogWrite(Motor_pwm_pin, pwmValue);  
        digitalWrite(Motor_dir_pin, HIGH);    
    }
    // Serial.println(pwmValue);  


    unsigned long currentTime = millis(); // stores current time
    long currentTicks = myEnc.read();

    
    // Serial.print("Ticks: ");
    // Serial.println(currentTicks);

    if (currentTime - prevTime >= 1000) {
        long tickDifference = currentTicks - prevTicks;
        rpm = (tickDifference / (float)Ticks_per_rev) * 60.0;  

        Serial.print("PWM: ");
        Serial.print(pwmValue);
        Serial.print(" | RPM: ");
        Serial.println(rpm);

        prevTicks = currentTicks;
        prevTime = currentTime;
    }
}