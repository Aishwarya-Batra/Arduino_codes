#include <Servo.h>
#include <Wire.h>
IntervalTimer myTimer;

#include <TFLI2C.h>      // TFLuna-I2C Library v.0.1.1
 
TFLI2C tflI2C;
 
int16_t  tfDist;    // distance in centimeters
int16_t  tfAddr = TFL_DEF_ADR;  // Use this default I2C address

 
Servo servo_left;
Servo servo_right;

int roller1_pin=21;
int roller1_spd=23;

int roller2_pin=20;
int roller2_spd=22;

int ball_push=16;
int ball_pull=17;

int piston1=38;
int piston2=39;

void servomotion(int start_angle, int end_angle){
  if(start_angle<end_angle){ 
       for(int angle=start_angle;angle<=end_angle;angle++){
        //if(angle<115)
        servo_right.write(180-angle);
        
        servo_left.write(angle);
        delay(15);
      }
    }
    else if(start_angle>end_angle){
      for(int angle=start_angle;angle>=end_angle;angle--){
      //if(angle<115)
        servo_right.write(180-angle);
        Serial.println(180-angle);
        
        servo_left.write(angle);
        Serial.println(angle);
        delay(15);
      }
    }
    
}


void rollers(){
 digitalWrite(roller1_pin,HIGH);
 analogWrite(roller1_spd,200);

 digitalWrite(roller2_pin,LOW);
 analogWrite(roller2_spd,200); 

}

void stoprollers(){
 digitalWrite(roller1_pin,LOW);
 analogWrite(roller1_spd,0);

 digitalWrite(roller2_pin,LOW);
 analogWrite(roller2_spd,0); 


}

void dcv_control(){
  digitalWrite(ball_push,LOW);
  digitalWrite(ball_pull,HIGH);
  delay(300);

  digitalWrite(ball_push,LOW);
  digitalWrite(ball_pull,LOW);
  delay(1000);

  digitalWrite(ball_push,HIGH);
  digitalWrite(ball_pull,LOW);

}
void tof(){
  if(tflI2C.getData(tfDist, tfAddr)){
       Serial.println(String(tfDist)+" cm / " + String(tfDist/2.54)+" inches");
    // }
  //delay(50);
  if(tfDist<25){
  digitalWrite(piston1,LOW);
  digitalWrite(piston2,HIGH);
  delay(1000);
  // digitalWrite(piston1,LOW);
  // digitalWrite(piston2,LOW);
  // delay(500);
  digitalWrite(piston1,HIGH);
  digitalWrite(piston2,LOW);
  

  }}
}

void start(){

  stoprollers();

  digitalWrite(ball_push,HIGH);
  digitalWrite(ball_pull,HIGH);

  digitalWrite(piston1,HIGH);
  digitalWrite(piston2,HIGH);

  servomotion(30,0);
  }

void run(){

   rollers();

  servomotion(0,130);
  //servo_right.write(130);
  delay(1500);
 
  dcv_control();

  myTimer.begin(tof,5000);
  delay(1000);

}

void end(){
  stoprollers();
  servomotion(130,0);
  
}
void setup() {
  Wire.begin(); //default sda and scl 18 19
  Serial.begin(115200);
  // wait until serial port opens for native USB devices
  // while (!Serial) {
  //   delay(1);
  // }

  servo_right.attach(14);
  servo_left.attach(15);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);

  pinMode(ball_push,OUTPUT);
  pinMode(ball_pull,OUTPUT);
  
  pinMode(roller1_pin, OUTPUT);
  pinMode(roller1_spd, OUTPUT);

  pinMode(roller2_pin, OUTPUT);
  pinMode(roller2_spd, OUTPUT);

  pinMode(piston1,OUTPUT);
  pinMode(piston2,OUTPUT);
  
  
}
int value;

void loop(){

  if(Serial.available()>0){
    String input = Serial.readStringUntil('\n');
    input.trim();
    value=input.substring(0,1).toInt();}
    Serial.println(value);
    if(value==1){
      start();
      value-=1;
    }
    else if(value==2){
      run();
      value-=2;
    }
    else if(value==3){
      end();
      value-=3;
    }
}
