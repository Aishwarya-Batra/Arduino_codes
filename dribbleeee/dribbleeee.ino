#include <Pixy2I2C.h>
#include <Servo.h>
Pixy2I2C pixy;
#include "USBHost_t36.h"

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
// int buttons=0;

int drb_dir_pin=10;   //..........................................
int drb_pwm_pin=11;
int limitswitch_out=19;
int limitswitch_in=22;        // rack and pinion
int counter=0;
bool switchout=1;
bool switchin=0;   //.................................................


int roller=28;

Servo servo_l; //dribbling left servo
Servo servo_r; //dribbling right servo

int dribble_piston[4]={31,32,26,27};
// index 0 & 1 -> ball push/pull(piston1)  index 2 & 3 -> ball catch(piston2)
// extend-> 2 & 0  retract-> 3 & 1 

void setup(){

  Serial.begin(9600);
  // Serial8.begin(115200);
  pixy.init();
  if (CrashReport) Serial.print(CrashReport);
  myusb.begin();

  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);

  analogWriteResolution(14);
  analogWriteFrequency(drb_pwm_pin,9000);

  pinMode(limitswitch_out,INPUT_PULLUP);
  pinMode(limitswitch_in,INPUT_PULLUP);
  pinMode(drb_dir_pin,OUTPUT);
  pinMode(drb_pwm_pin,OUTPUT);

  digitalWrite(drb_dir_pin,LOW);
  analogWrite(drb_pwm_pin,0);

  pinMode(roller,OUTPUT);
  digitalWrite(roller,HIGH);//stop position

  //.....dribble_servos_initialise..........
  servo_l.attach(2);
  servo_r.attach(1);
  servo_l.write(180);
  servo_r.write(0);
  //........................................

  //......dribble_pistons_initialise......
  for(int i=0;i<4;i++){
    pinMode(dribble_piston[i],OUTPUT);
  }
  digitalWrite(dribble_piston[2],LOW); //piston1 at initial position
  digitalWrite(dribble_piston[3],HIGH);
  digitalWrite(dribble_piston[0],LOW);  // piston2 at initial position
  digitalWrite(dribble_piston[1],HIGH);

  delay(500);
  for(int i=0;i<4;i++){
    digitalWrite(dribble_piston[i],LOW);
  }
  //............................................
 
}

void servomotion(int start_angle, int end_angle){
  if(start_angle<end_angle){ 
    for(int angle=start_angle;angle<=end_angle;angle++){
    servo_r.write(angle);

    servo_l.write(180-angle);
    delay(15);
    }
  }
  else if(start_angle>end_angle){
    for(int angle=start_angle;angle>=end_angle;angle--){
    servo_r.write(angle);
    //Serial.println(180-angle);
    servo_l.write(180-angle);
    //Serial.println(angle);
    delay(15);
    }
  }     
}

void dribble(){
  myusb.Task();
   buttons=0;
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
  Serial.print("out:");
  Serial.print(switchout);
  Serial.print(" in:");
  Serial.println(switchin);

  if(counter==0){
    if(buttons==4){
      digitalWrite(drb_dir_pin,LOW);
      analogWrite(drb_pwm_pin,64*255);
    }
    else if(switchin==0){
      digitalWrite(drb_dir_pin,LOW);
      analogWrite(drb_pwm_pin,0);
      counter=1;
      servomotion(0,85);
      delay(100);

  digitalWrite(dribble_piston[2],HIGH);
  digitalWrite(dribble_piston[3],LOW);
  delay(500);
  digitalWrite(dribble_piston[2],LOW);
  digitalWrite(dribble_piston[3],LOW);
  delay(500);
  
  digitalWrite(dribble_piston[2],LOW);
  digitalWrite(dribble_piston[3],HIGH);
  delay(400);

  digitalWrite(roller,LOW);
  digitalWrite(dribble_piston[2],LOW);
  digitalWrite(dribble_piston[3],LOW);
  delay(400);

  pixy.setLamp(1, 1);
  while (true) {
      Serial.println("pixy_while");
      pixy.ccc.getBlocks();
      if (pixy.ccc.numBlocks) {
        digitalWrite(dribble_piston[1],LOW);
        digitalWrite(dribble_piston[0],HIGH); 
        delay(500);
        digitalWrite(dribble_piston[1],HIGH);
        digitalWrite(dribble_piston[0],LOW);
        delay(500);
        Serial.println("Detected");
        pixy.setLamp(0, 0);
        break;
      }
    }
    digitalWrite(roller,HIGH);
    servomotion(95,0);
    for(int i=0;i<4;i++){
    digitalWrite(dribble_piston[i],LOW);
  }
  
   }
  }
  else if(counter==1){
    if(buttons==4){
      digitalWrite(drb_dir_pin,HIGH);
      analogWrite(drb_pwm_pin,32*255);
    }
    else if(switchout==0){
      digitalWrite(drb_dir_pin,HIGH);
      analogWrite(drb_pwm_pin,0);
      counter=0;
    }
  }
  
 
}
// int value=0;
void loop(){
  dribble();

}





//   if (Serial8.available() >= sizeof(buttons)){
//   Serial8.readBytes((char*)&buttons, sizeof(buttons));
//   Serial.print("button: ");
//   Serial.println(buttons);
// }

// if(buttons==0){
//   dribble();

// }
  //  if (Serial.available() > 0) {  // Check if data is available
  //       String input = Serial.readStringUntil('\n');  // Read input
  //       input.trim();  // Remove any whitespace
  //       value = input.toInt();  // Convert the entire string to an integer

  //   }              
  //   Serial.println(value);

  //   if(value==1){ 
  //     dribble();
  //     value-=1;
  //   }


