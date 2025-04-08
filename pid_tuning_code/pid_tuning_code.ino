#include "USBHost_t36.h"
#include <Encoder.h>
#include <IntervalTimer.h>

#define Encoder_A 17
#define Encoder_B 16
#define Ticks_per_rev 700

IntervalTimer rpm_time; 


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

int Motor_pwm_pin =3 ; 
int Motor_dir_pin =2 ;

Encoder myEnc(Encoder_A, Encoder_B);

// PID Gains
float kp = 5.8 ;  
float ki = 150; 
float kd = 0.65; // 5.8 150 0.65

float timePid = 0.050;

// Speed Control Variable

float setSpeed=0;
float ps_value=0;
volatile long prevTicks = 0;
// unsigned long prevTime = 0;
float rpm = 0; 
float currentSpeed = 0;   
float error=0.0, integralError = 0.0, lastError = 0.0, derivativeError=0;
float motorOutput = 0.0;


void rpm_calculate() {

   myusb.Task();
   if (joystick1.available()) {
    for (uint8_t i = 0; i < 64; i++) {
      psAxis_prev[i] = psAxis[i];
      psAxis[i] = joystick1.getAxis(i);
    }
    buttons = joystick1.getButtons();
    ps_value= map(psAxis[0],0,255,-127,127);
    
  
  }

    // unsigned long currentTime = millis(); 
    long currentTicks = myEnc.read();

    setSpeed=map(ps_value,-127,127,-200,200); 
    Serial.print("set_rpm:");
    Serial.print(setSpeed);


    // Compute RPM
    long tickDifference = currentTicks - prevTicks; 
    currentSpeed = ((tickDifference / (float)Ticks_per_rev) * 60.0) / timePid; 
    prevTicks = currentTicks; 
    Serial.print(" calculated_rpm:");
    Serial.print(currentSpeed);

    // PID Control
    error = (setSpeed - currentSpeed);
    integralError = integralError+(error*timePid); 
    derivativeError = (error - lastError) / timePid;
    lastError = error;  


    // Compute motor output
    motorOutput = (kp * error) + (ki * integralError) + (kd * derivativeError);
    motorOutput = constrain(motorOutput, -16383, 16383);
    // Serial.print(" output_pwm:");
    // Serial.println(motorOutput);
    Serial.println();

    
    if (motorOutput >= 0) {
    digitalWrite(Motor_dir_pin, HIGH);
    } 
    else {
    digitalWrite(Motor_dir_pin, LOW);
    }
    analogWrite(Motor_pwm_pin,(int)fabs(motorOutput));
    // lastError = error;  

    
}

void setup() {
    Serial.begin(9600);

    if (CrashReport) Serial.print(CrashReport);
    myusb.begin();
    
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);

    analogWriteResolution(14);
    analogWriteFrequency(Motor_pwm_pin,9000);

    rpm_time.begin(rpm_calculate, 50000); // Call rpm_calculate every 100ms
    
    pinMode(Motor_pwm_pin, OUTPUT);
    pinMode(Motor_dir_pin, OUTPUT);

    // prevTime = millis(); 
    
    
}

void loop() {
  // if (Serial.available() > 0) {
  //   String input = Serial.readStringUntil('\n');   //kp ki kd
  //   input.trim();  

  //   int fSpace = input.indexOf(' ');
  //   int sSpace = input.indexOf(' ', fSpace + 1);

    
  //   kp = input.substring(0, fSpace).toFloat();
  //   ki = input.substring(fSpace + 1, sSpace).toFloat();
  //   kd = input.substring(sSpace + 1).toFloat();
    
  // }
  // Serial.printf("Kp:%f Ki:%f Kd:%f\n ",kp,ki,kd);
}

