#include<Servo.h>
#include<Wire.h>
#include<Pixy2I2C.h>
Pixy2I2C pixy;

Servo servo_left;
Servo servo_right;
Servo servo_stopper;

int dcv_catch_in;
int dcv_catch_out;

int dcv_push_in;
int dcv_push_out;

int dcv_dribble_out;
int dcv_dribble_in;

int roller_direction;
int roller_speed;


void setup(){
  //Wire.begin();
  Serial.begin(115200);

  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  
  servo_stopper.attach(1);
  servo_left.attach(2);
  servo_right.attach(3);
  servo_stopper.write(0);

  pinMode(dcv_push_in,OUTPUT);
  pinMode(dcv_catch_out,OUTPUT);
  //
  digitalWrite(dcv_catch_in,LOW);
  digitalWrite(dcv_catch_out,LOW);

  pinMode(dcv_push_in,OUTPUT);
  pinMode(dcv_push_out,OUTPUT);
  //
  digitalWrite(dcv_push_in,LOW);
  digitalWrite(dcv_push_out,LOW);

  pinMode(dcv_dribble_out,OUTPUT);
  pinMode(dcv_dribble_in,OUTPUT);
  //
  digitalWrite(dcv_dribble_out,LOW);
  digitalWrite(dcv_dribble_in,LOW);

  pinMode(roller_direction,OUTPUT);
  pinMode(roller_speed,OUTPUT);
  

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

void stoprollers(){
 digitalWrite(roller_direction,LOW);
 analogWrite(roller_speed,0);

}

void run_rollers(){
  digitalWrite(roller_direction,HIGH);
  analogWrite(roller_speed,150);

}

void ball_push_mechanism(){
  digitalWrite(dcv_push_in,HIGH);
  digitalWrite(dcv_push_out,LOW);
  delay(2000);

  digitalWrite(dcv_push_in,LOW);
  digitalWrite(dcv_push_out,HIGH);

}

void ball_catch_mechanism(){
  digitalWrite(dcv_push_in,HIGH);
  digitalWrite(dcv_push_out,LOW);
  delay(2000);

  digitalWrite(dcv_push_in,LOW);
  digitalWrite(dcv_push_out,HIGH);
}

void pixy_(){
  pixy.setLamp(1, 1);
    while (true) {
      pixy.ccc.getBlocks();

      if (pixy.ccc.numBlocks) {
        dcv_catch_mechanism();
        Serial.println("Detected");
        pixy.setLamp(0, 0);
        break;
      }

      if (joystick1.getButtons()){
        Serial.println("Overridden");
        break;
      }
  }
}


int value=0;
void loop(){

  if (Serial.available() > 0) {  // Check if data is available
        String input = Serial.readStringUntil('\n');  // Read input
        input.trim();  // Remove any whitespace
        value = input.toInt();  // Convert the entire string to an integer

        //Serial.print("Received value: ");
    }             
     Serial.println(value);

     if(value==1){

       servo_stopper.write(180);
       digitalWrite(dcv_dribble_out,HIGH);
       digitalWrite(dcv_dribble_in,LOW);
       run_rollers();
       servomotion(0,90);
       pixy_();

       value-=1;
     }

     else if(value==2){
      servo_stopper.write(0);
      stop_rollers();
      servomotion(90,0);
      digitalWrite(dcv_dribble_out,LOW);
      digitalWrite(dcv_dribble_in,HIGH);

      value-=2;
     }



}


