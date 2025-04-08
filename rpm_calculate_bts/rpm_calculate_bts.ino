#include <Encoder.h>
#include "USBHost_t36.h"
#include <IntervalTimer.h>

#define Encoder_A 22 //22 16 15
#define Encoder_B 23 //23 17 14
#define Ticks_per_rev 700

// #define EN_L 3
// #define EN_R 4
// 

IntervalTimer rpm_time; 

int LPWM=29;//29  2  9
int RPWM =5;//5  3  8


Encoder myEnc(Encoder_A, Encoder_B);

USBHost myusb;
USBHub hub1(myusb);
USBHIDParser hid1(myusb);
JoystickController joystick1(myusb);
// BluetoothController bluet (myusb, true, "0000");   // Version does pairing to device
BluetoothController bluet(myusb);  // version assumes it already was paireduint32_t buttons_prev = 0;
uint32_t buttons;

int psAxis[64];
int psAxis_prev[64];
bool first_joystick_message = true;


volatile long prevTicks = 0;
float rpm = 0;
int pwmValue= 0;  

void rpm_calculate() {

  myusb.Task();
   if (joystick1.available()) {
    for (uint8_t i = 0; i < 64; i++) {
      psAxis_prev[i] = psAxis[i];
      psAxis[i] = joystick1.getAxis(i);
    }
    // buttons = joystick1.getButtons();
    pwmValue= map(psAxis[0],0,255,-127,127);
    Serial.print("PWM: ");
    Serial.print(pwmValue);
    Serial.println("");
    
    // Serial.println(buttons);
  
    }
    // unsigned long currentTime = millis(); 
    long currentTicks = myEnc.read(); 

    long tickDifference = currentTicks - prevTicks; 
    rpm = ((tickDifference / (float)Ticks_per_rev) * 60.0) / 0.05;  
    prevTicks = currentTicks; 

    Serial.print(" RPM: ");
    Serial.println(rpm);


    if (pwmValue >= 0) {
    analogWrite(RPWM,pwmValue);
    analogWrite(LPWM,0);
    } 
    else {
    analogWrite(LPWM,abs(pwmValue));
    analogWrite(RPWM,0);
    } 

}
void setup() {
    Serial.begin(9600);
    
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    // analogWriteResolution(14);
    // analogWriteFrequency(,9000);

    if (CrashReport) Serial.print(CrashReport);
    myusb.begin();

    rpm_time.begin(rpm_calculate, 50000);
    
    pinMode(LPWM, OUTPUT);
    pinMode(RPWM, OUTPUT);
    // pinMode(EN_L,OUTPUT);
    // pinMode(EN_R,OUTPUT);

    // digitalWrite(EN_L,HIGH);
    // digitalWrite(EN_R,HIGH);

    
    // prevTime = millis(); 
}

void loop() {
    // if (Serial.available() > 0) {  // Check if data is available
    //     String input = Serial.readStringUntil('\n'); 
    //     input.trim();  
    //     pwmValue = input.toInt(); 

    // //     analogWrite(Motor_pwm_pin, pwmValue); 
    // //     digitalWrite(Motor_dir_pin, HIGH); 

    // }
}
