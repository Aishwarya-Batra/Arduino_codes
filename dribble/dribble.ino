#include <Pixy2I2C.h>
#include <Servo.h>
Pixy2I2C pixy;

int roller=28;
int roller_c=0;
// int buttons=0;

Servo servo_l; //dribbling left servo
Servo servo_r;

int piston[4]={31,32,26,27};
// index 0 & 1 -> ball push/pull(piston1)  index 2 & 3 -> ball catch(piston2)
// extend-> 2 & 0  retract-> 3 & 1 

void setup(){

  Serial.begin(9600);
  // Serial8.begin(115200);
  pixy.init(); 


  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);

  pinMode(roller,OUTPUT);
  digitalWrite(roller,HIGH);

  //.....dribble_servos_initialise..........
  servo_l.attach(2);
  servo_r.attach(1);
  servo_l.write(180);
  servo_r.write(0);
  //........................................

  //......dribble_pistons_initialise......
  for(int i=0;i<4;i++){
    pinMode(piston[i],OUTPUT);
  }
  digitalWrite(piston[2],LOW); //piston1 at initial position
  digitalWrite(piston[3],HIGH);
  digitalWrite(piston[0],LOW);  // piston2 at initial position
  digitalWrite(piston[1],HIGH);

  delay(500);
  for(int i=0;i<4;i++){
    digitalWrite(piston[i],LOW);
  }
  //............................................
 
}

void servomotion(int start_angle, int end_angle){
  if(start_angle<end_angle){ 
    for(int angle=start_angle;angle<=end_angle+6;angle++){
    
    servo_r.write(angle);
    if(angle<end_angle){
    servo_l.write(180-angle);}
    delay(15);
    }
  }
  else if(start_angle>end_angle){
    for(int angle=start_angle;angle>=end_angle;angle--){
    // if(angle<125)
    servo_r.write(angle);
    //Serial.println(180-angle);
    servo_l.write(180-angle);
    //Serial.println(angle);
    delay(15);
    }
  }     
}

void piston1(){  // ball push/pull
  servomotion(0,85);
  delay(100);
  digitalWrite(piston[2],HIGH);
  digitalWrite(piston[3],LOW);
  delay(500);
  digitalWrite(piston[2],LOW);
  digitalWrite(piston[3],LOW);
  delay(500);
  
  digitalWrite(piston[2],LOW);
  digitalWrite(piston[3],HIGH);
  delay(500);

  digitalWrite(roller,LOW);
  digitalWrite(piston[2],LOW);
  digitalWrite(piston[3],LOW);
  delay(400);
  pixy.setLamp(1, 1);
  while (true) {
      Serial.println("pixy_while");
      pixy.ccc.getBlocks();
      if (pixy.ccc.numBlocks) {
        digitalWrite(piston[1],LOW);
        digitalWrite(piston[0],HIGH); 
        delay(500);
        digitalWrite(piston[1],HIGH);
        digitalWrite(piston[0],LOW);
        delay(500);
        Serial.println("Detected");
        pixy.setLamp(0, 0);
        break;
      }
    }
    digitalWrite(roller,HIGH);
    servomotion(85,0);
    for(int i=0;i<4;i++){


    digitalWrite(piston[i],LOW);
  }
}
void piston2(){    // ball catch

digitalWrite(piston[2],HIGH);
  digitalWrite(piston[3],LOW);
  delay(500);
  digitalWrite(piston[2],LOW);
  digitalWrite(piston[3],LOW);
  delay(500);
  
  digitalWrite(piston[2],LOW);
  digitalWrite(piston[3],HIGH);
  delay(300);

  digitalWrite(roller,LOW);
  digitalWrite(piston[2],LOW);
  digitalWrite(piston[3],LOW);
delay(1000);
  digitalWrite(piston[2],HIGH);
  digitalWrite(piston[3],LOW);
  delay(500);
  digitalWrite(piston[2],LOW);
  digitalWrite(piston[3],LOW);
  delay(500);
  
  digitalWrite(piston[2],LOW);
  digitalWrite(piston[3],HIGH);
  delay(400);

  digitalWrite(roller,LOW);
  digitalWrite(piston[2],LOW);
  digitalWrite(piston[3],LOW);
  

}
void rollers(){
  if(roller_c==0){
    digitalWrite(roller,LOW);
    // analogWrite(roller,100);
    roller_c=1;
  }
  else if(roller_c==1){
    digitalWrite(roller,HIGH);
    // analogWrite(roller,0);
    roller_c=0;
  }
  
}
int value=0;
void loop()
{
//Serial.println("Okay");
if (Serial.available() > 0) {  // Check if data is available
        String input = Serial.readStringUntil('\n');  // Read input
        input.trim();  // Remove any whitespace
        value = input.toInt();  // Convert the entire string to an integer

    }              
    Serial.println(value);


//Serial.println(value);


    if(value==1){ 
      rollers();
      value-=1;
    }
    else if(value==2){ // ball push/pull
      piston1();
      value-=2;
    }
    else if(value==3){ // ball catch
      piston2();
      value-=3;
    }
    else if(value==4){
      servomotion(0,85);
      value-=4;
    }
    else if(value==5){
      servomotion(85,0);

      value-=5;
    }
}