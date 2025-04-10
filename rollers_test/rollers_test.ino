#include<Servo.h>
int roller1_pin=38;//left
int roller1_spd=14;

int roller2_pin=17;//right
int roller2_spd=19;

Servo servo_left;
Servo servo_right;


void setup(){
  servo_left.attach(37);
  servo_right.attach(36);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);

  pinMode(roller1_pin, OUTPUT);
  pinMode(roller1_spd, OUTPUT);

  pinMode(roller2_pin, OUTPUT);
  pinMode(roller2_spd, OUTPUT);
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
 digitalWrite(roller1_pin,HIGH);
 analogWrite(roller1_spd,255);

 digitalWrite(roller2_pin,HIGH);
 analogWrite(roller2_spd,255); 

}

void stoprollers(){
 digitalWrite(roller1_pin,LOW);
 analogWrite(roller1_spd,0);

 digitalWrite(roller2_pin,LOW);
 analogWrite(roller2_spd,0); 


}
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
      //servomotion(0,135);
      //rollers();
      servomotion(0,135);
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
    else if(value==3){
      //servomotion(135,0);
      rollers();
      value=-3;
    }
    }

