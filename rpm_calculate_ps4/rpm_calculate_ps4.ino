#include <Encoder.h>
#include "USBHost_t36.h"

// bool isJoystick=0;

#define Encoder_A 9
#define Encoder_B 8 
#define Ticks_per_rev 701 

int Motor_pwm_pin=1; 
int Motor_dir_pin=0; 

Encoder myEnc(Encoder_A, Encoder_B);

USBHost myusb;
USBHub hub1(myusb);
USBHIDParser hid1(myusb);
JoystickController joystick1(myusb);
//BluetoothController bluet(myusb, true, "0000");   // Version does pairing to device
// BluetoothController bluet(myusb);  // version assumes it already was paireduint32_t buttons_prev = 0;
// uint32_t buttons;

//int psAxis[1];
//bool first_joystick_message = true;
//uint8_t last_bdaddr[6] = {0, 0, 0, 0, 0, 0};

volatile long prevTicks = 0;
unsigned long prevTime = 0;
float rpm = 0;
int pwmValue ;  

void setup() {
    Serial.begin(115200);
    myusb.begin();

    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    
    // pinMode(Encoder_A, INPUT_PULLUP);
    // pinMode(Encoder_B, INPUT_PULLUP);

    pinMode(13,OUTPUT);
    digitalWrite(13,HIGH);
    
    pinMode(Motor_pwm_pin, OUTPUT);
    pinMode(Motor_dir_pin, OUTPUT);
    
    prevTime = millis();  // stores initial time
}

void loop() {

  myusb.Task();

  if (joystick1.available() > 0) {  // Check if data is available
    
      int value=joystick1.getAxis(1);
      pwmValue= map(value,0,255,-127,127);

      if(pwmValue<0){
        digitalWrite(Motor_dir_pin, LOW);  
      
      }
      else{
        digitalWrite(Motor_dir_pin, HIGH);
      }
        
      analogWrite(Motor_pwm_pin, abs(pwmValue));  
       
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