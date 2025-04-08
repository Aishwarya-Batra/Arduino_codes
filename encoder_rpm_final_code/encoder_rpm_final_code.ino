#include <Encoder.h>
#include "USBHost_t36.h"
#include <IntervalTimer.h>

#define Encoder_A 8
#define Encoder_B 9 
#define Ticks_per_rev 700

IntervalTimer rpm_time; 

int Motor_pwm_pin = 1; 
int Motor_dir_pin = 0;

Encoder myEnc(Encoder_A, Encoder_B);

USBHost myusb;
USBHub hub1(myusb);
USBHIDParser hid1(myusb);
JoystickController joystick1(myusb);
BluetoothController bluet (myusb, true, "0000");   // Version does pairing to device
//BluetoothController bluet(myusb);  // version assumes it already was paireduint32_t buttons_prev = 0;
uint32_t buttons;

int psAxis[64];
int psAxis_prev[64];
bool first_joystick_message = true;


volatile long prevTicks = 0;
// unsigned long prevTime = 0;
// float ps_value=0;
float rpm = 0;
int pwmValue = 0;  

void rpm_calculate() {

  myusb.Task();
   if (joystick1.available()) {
    for (uint8_t i = 0; i < 64; i++) {
      psAxis_prev[i] = psAxis[i];
      psAxis[i] = joystick1.getAxis(i);
    }
    buttons = joystick1.getButtons();
    pwmValue= map(psAxis[0],0,255,-127,127);
    Serial.print("PWM: ");
    Serial.print(pwmValue);
    Serial.println("");
    
    // Serial.println(buttons);
  
    }
    // unsigned long currentTime = millis(); 
    long currentTicks = myEnc.read(); 

    long tickDifference = currentTicks - prevTicks; 
    rpm = ((tickDifference / (float)Ticks_per_rev) * 60.0) / 0.075;  
    prevTicks = currentTicks; 

    Serial.print(" RPM: ");
    Serial.println(rpm);


    if (pwmValue >= 0) {
    digitalWrite(Motor_dir_pin, HIGH);
    } 
    else {
    digitalWrite(Motor_dir_pin, LOW);
    }
    analogWrite(Motor_pwm_pin,abs(pwmValue*64));
    


    // Serial.print("PWM: ");
    // Serial.print(pwmValue);
    
    
    // prevTime = currentTime;  

}
void setup() {
    Serial.begin(9600);
    
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    analogWriteResolution(14);
    analogWriteFrequency(Motor_pwm_pin,9000);

    if (CrashReport) Serial.print(CrashReport);
    myusb.begin();

    rpm_time.begin(rpm_calculate, 75000);
    
    pinMode(Motor_pwm_pin, OUTPUT);
    pinMode(Motor_dir_pin, OUTPUT);

    
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
