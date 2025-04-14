#include "USBHost_t36.h"

int drb_dir_pin=10;
int drb_pwm_pin=11;
int limitswitch_out=19;
int limitswitch_in=22;
int counter=0;
bool switchout=1;
bool switchin=0;

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

void ball_dribble(){
  myusb.Task();
   if (joystick1.available()) {
    for (uint8_t i = 0; i < 64; i++) {
      psAxis_prev[i] = psAxis[i];
      psAxis[i] = joystick1.getAxis(i);
    }
     buttons = joystick1.getButtons();
    //  Serial.println(buttons);
    }
  switchout = digitalRead(limitswitch_out);
  switchin = digitalRead(limitswitch_in);
  Serial.print("up:");
  Serial.print(switchout);
  Serial.print(" down:");
  Serial.print(switchin);
  Serial.print(" counter:");
  Serial.println(counter);


  if(counter==0){   
    if(buttons==4){
      digitalWrite(drb_dir_pin,LOW);
      analogWrite(drb_pwm_pin,64*255);
    }
    else if(switchin==0){
      digitalWrite(drb_dir_pin,LOW);
      analogWrite(drb_pwm_pin,0);
      counter=1;
      

    }
  }
  else if(counter==1){
    if(buttons==4){
      digitalWrite(drb_dir_pin,HIGH);
      analogWrite(drb_pwm_pin,64*255);
    }
    else if(switchout==0){
      digitalWrite(drb_dir_pin,HIGH);
      analogWrite(drb_pwm_pin,0);
      counter=0;
    }
  }
 
}

void setup(){

  Serial.begin(9600);
    
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  if (CrashReport) Serial.print(CrashReport);
  myusb.begin();

  analogWriteResolution(14);
  analogWriteFrequency(drb_pwm_pin,9000);

  pinMode(limitswitch_out,INPUT_PULLUP);
  pinMode(limitswitch_in,INPUT_PULLUP);
  pinMode(drb_dir_pin,OUTPUT);
  pinMode(drb_pwm_pin,OUTPUT);

  digitalWrite(drb_dir_pin,LOW);
  analogWrite(drb_pwm_pin,0);


}

void loop(){
  ball_dribble(); 
}


