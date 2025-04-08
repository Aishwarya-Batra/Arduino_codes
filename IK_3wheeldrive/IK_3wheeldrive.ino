#include "USBHost_t36.h"

USBHost myusb;
USBHIDParser hid1(myusb);
JoystickController ps4(myusb);
BluetoothController bluet(myusb, true, "0000");

int dir1=2;
int dir2=6;
int dir3=4;
int Ena1=3;
int Ena2=7;
int Ena3=5;
int led=13;

int xaxis;
int yaxis;
int waxis;
int V1;
int V2;
int V3;
int speed1;
int speed2;
int speed3;

void setup() {
  pinMode(13,OUTPUT);
  pinMode(dir1,OUTPUT);
  pinMode(dir2,OUTPUT);
  pinMode(dir3,OUTPUT);
  pinMode(Ena1,OUTPUT);
  pinMode(Ena2,OUTPUT);
  pinMode(Ena3,OUTPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  myusb.begin();
  digitalWrite(led,HIGH);


}

void loop() {
  myusb.Task();
  if (ps4.available()){
      xaxis=map(ps4.getAxis(2),0,255,-127,127);
      yaxis=map(ps4.getAxis(5),0,255,127,-127);
      waxis=(map(ps4.getAxis(0),0,255,-127,127));
      V1=(0.333*waxis)-(0.666*xaxis);
      V2=(0.333*waxis)+(0.333*xaxis)-(0.577*yaxis);
      V3=(0.333*xaxis)+(0.577*yaxis)+(0.333*waxis);
      speed1=map(V1,0,100,0,200);
      speed2=map(V2,0,100,0,200);
      speed3=map(V3,0,100,0,200);
      // Serial.printf( "V1="); 
      // Serial.println( V1);
      // Serial.printf( "V2=");
      // Serial.println(V2);
      // Serial.printf( "V3=");
      // Serial.println(V3);
      // Serial.printf( "pwmV1=");
      // Serial.println(speed1);
      // Serial.printf( "pwmV2=");
      // Serial.println(speed2);
      // Serial.printf( "pwmV3=");
      // Serial.println(speed3);
      // delay(100);
    }

  motorOn(speed1, Ena1, dir1); // Call for Motor 1
  motorOn(speed2, Ena2, dir2); // Call for Motor 2
  motorOn(speed3, Ena3, dir3); // Call for Motor 3
}

  



void motorOn(int speed,int Mot,int dir){
  if (speed<0){
    digitalWrite(dir,LOW);
  }
  else{
    digitalWrite(dir,HIGH);
  }
  analogWrite(Mot,abs(speed)); 

}