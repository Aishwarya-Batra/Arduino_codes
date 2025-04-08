

#include <Servo.h>
#include <Wire.h>
IntervalTimer myTimer;

#include <TFLI2C.h>      // TFLuna-I2C Library v.0.1.1
 
TFLI2C tflI2C;
 
int16_t  tfDist;    // distance in centimeters
int16_t  tfAddr = TFL_DEF_ADR;  // Use this default I2C address

 
Servo servo_left;
Servo servo_right;

int roller1_pin=38;//left
int roller1_spd=14;

int roller2_pin=17;//right
int roller2_spd=19;

// int piston1=;
// int piston2=;

// int ball_push=;
//int ball_pull=;


// digitalWrite(piston1,HIGH);
//   digitalWrite(piston2,LOW);
//   delay(1000);
//   // digitalWrite(piston1,LOW);
//   // digitalWrite(piston2,LOW);
//   // delay(500);
//   digitalWrite(piston1,LOW);
//   digitalWrite(piston2,HIGH);
  

  
void setup() {
  Wire.begin(); //default sda and scl 18 19
  Serial.begin(115200);
  //myTimer.begin(tof,5000);
  //delay(1000);
  // wait until serial port opens for native USB devices
  // while (!Serial) {
  //   delay(1);
  // }

  servo_left.attach(37);
  servo_right.attach(36);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);

  // pinMode(ball_push,OUTPUT);
  // pinMode(ball_pull,OUTPUT);
  // digitalWrite(ball_push,LOW);
  // digitalWrite(ball_pull,LOW);
  
  pinMode(roller1_pin, OUTPUT);
  pinMode(roller1_spd, OUTPUT);

  pinMode(roller2_pin, OUTPUT);
  pinMode(roller2_spd, OUTPUT);

  // pinMode(piston1,OUTPUT);
  // pinMode(piston2,OUTPUT);


  
  //servo_left.write(180);
  for(int angle=30;angle>=0;angle--){
      if(angle<125)
          servo_right.write(180-angle);
        //Serial.println(180-angle);
        
        servo_left.write(angle);
        Serial.println(angle);
        delay(15);
      }
}
void servomotion(int start_angle, int end_angle){
  if(start_angle<end_angle){ 
       for(int angle=start_angle;angle<=end_angle;angle++){
        if(angle<125)
          servo_right.write(180-angle);
        
        servo_left.write(angle);
        delay(15);
      }
    }
    else if(start_angle>end_angle){
      for(int angle=start_angle;angle>=end_angle;angle--){
      if(angle<125)
        servo_right.write(180-angle);
        //Serial.println(180-angle);
        
        servo_left.write(angle);
        //Serial.println(angle);
        delay(15);
      }
    }
    
}

void rollers(){
 digitalWrite(roller1_pin,LOW);
 analogWrite(roller1_spd,200);

 digitalWrite(roller2_pin,LOW);
 analogWrite(roller2_spd,200); 

}

void stoprollers(){
 digitalWrite(roller1_pin,HIGH);
 analogWrite(roller1_spd,0);

 digitalWrite(roller2_pin,HIGH);
 analogWrite(roller2_spd,0); 


}
// void dcv_control(){
//   digitalWrite(ball_push,LOW);
//   digitalWrite(ball_pull,HIGH);
//   delay(1000);

//   // digitalWrite(ball_push,LOW);
//   // digitalWrite(ball_pull,LOW);
//   // delay(1000);

//   digitalWrite(ball_push,HIGH);
//   digitalWrite(ball_pull,LOW);

// }
// void tof(){
//   if(tflI2C.getData(tfDist, tfAddr)){
//        Serial.println(String(tfDist)+" cm / " + String(tfDist/2.54)+" inches");
//     // }
//   //delay(50);
//   if(tfDist<25){
//   digitalWrite(piston1,HIGH);
//   digitalWrite(piston2,LOW);
//   delay(1000);
//   // digitalWrite(piston1,LOW);
//   // digitalWrite(piston2,LOW);
//   // delay(500);
//   digitalWrite(piston1,LOW);
//   digitalWrite(piston2,HIGH);
  

//   }}
//}
// void function(){
//   digitalWrite(piston1,HIGH);
//   digitalWrite(piston2,LOW);
//   delay(1000);
//   // digitalWrite(piston1,LOW);
//   // digitalWrite(piston2,LOW);
//   // delay(500);
//   digitalWrite(piston1,LOW);
//   digitalWrite(piston2,HIGH);
  
// }


int value=0;
void loop()
{
//Serial.println("Okay");
if (Serial.available() > 0) {  // Check if data is available
        String input = Serial.readStringUntil('\n');  // Read input
        input.trim();  // Remove any whitespace
        value = input.toInt();  // Convert the entire string to an integer

        //Serial.print("Received value: ");
    }              Serial.println(value);


//Serial.println(value);


    if(value==1){
      rollers();
      void servomotion(int start_angle, int end_angle){
  if(start_angle<end_angle){ 
       for(int angle=start_angle;angle<=end_angle;angle++){
        if(angle<125)
          servo_right.write(180-angle);
        
        servo_left.write(angle);
        delay(15);
      }
    }
    else if(start_angle>end_angle){
      for(int angle=start_angle;angle>=end_angle;angle--){
      if(angle<125)
        servo_right.write(180-angle);
        //Serial.println(180-angle);
        
        servo_left.write(angle);
        //Serial.println(angle);
        delay(15);
      }
    }
    
}
    //dcv_control();
    //function();
      //tof();
      value-=1;
    }
    else if(value==2){
      servomotion(135,0);
      stoprollers();
      value=-2;
    }
    }
