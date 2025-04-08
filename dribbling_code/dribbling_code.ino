#include <Servo.h>
#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// tof connection sda and scl
 
Servo servo_left;
Servo servo_right;

int roller1_pin=21;
int roller1_spd=23;

int roller2_pin=20;
int roller2_spd=22;

int ball_push=19;
int ball_pull=18;

int piston1=16;
int piston2=17;


// float easeInOutQuint(float x) {
//   return (x < 0.5) ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2;
// }

// void servomotion(int startPos, int endPos, int duration){
//   int steps = 100;
//   for (int i = 0; i <= steps; i++) {
//     float progress = (float)i / steps; 
//     float easedProgress = easeInOutQuint(progress); 
//     int servoPos = startPos + (endPos - startPos) * easedProgress; 
//     servo_left.write(servoPos);
//     servo_right.write(180-servoPos); 
//     delay(duration / steps); 
//   }
// }

void servomotion(int start_angle, int end_angle){
  if(start_angle<end_angle){ 
       for(int angle=start_angle;angle<=end_angle;angle++){
        servo_left.write(angle);
        //delay(15);
        
        servo_right.write(180-angle);
        delay(15);
      }
    }
    else if(start_angle>end_angle){
      for(int angle=start_angle;angle>=end_angle;angle--){
        servo_left.write(angle);
        //delay(15);
        servo_right.write(180-angle);
        delay(15);
      }
    }
    
}

void rollers(){
 digitalWrite(roller1_pin,HIGH);
 analogWrite(roller1_spd,150);

 digitalWrite(roller2_pin,LOW);
 analogWrite(roller2_spd,150); 

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

void setup() {
  //Wire.begin(); //default sda and scl 18 19
  Serial.begin(115200);
  // wait until serial port opens for native USB devices
  // while (!Serial) {
  //   delay(1);
  // }

  servo_left.attach(15);
  servo_right.attach(14);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  //servomotion(180,60);

  pinMode(ball_push,OUTPUT);
  pinMode(ball_pull,OUTPUT);
  digitalWrite(ball_push,HIGH);
  digitalWrite(ball_pull,HIGH);

  pinMode(roller1_pin, OUTPUT);
  pinMode(roller1_spd, OUTPUT);

  pinMode(roller2_pin, OUTPUT);
  pinMode(roller2_spd, OUTPUT);
  
  stoprollers();
  servomotion(180,60);
  servo_right.write(135);
  delay(500);

  // pinMode(piston1,OUTPUT);
  // pinMode(piston2,OUTPUT);
  // digitalWrite(piston1,HIGH);
  // digitalWrite(piston2,HIGH);


  // Initialize the sensor
  // Serial.println("Adafruit VL53L0X test");
  // delay(100);
  // Serial.println("---");
  // if (!lox.begin()) {
  //   Serial.println(F("Failed to boot VL53L0X"));
  //   while (1); // stops the program if it can't be initialised
  // }
  




  // if (Serial.available()>0){
  //   String input = Serial.readStringUntil('\n');
  //   input.trim();
  //   int Spos = input.substring(0,3).toInt();
  //   int Epos = input.substring(3,6).toInt();
  //   int dur = input.substring(6,input.length()).toInt();
  //   int time = dur*1000;

  //   servomotion(Spos,Epos,time);
  // servomotion(Spos,Epos,time);
  // }
  // servomotion(180,60);
  // servo_left.write(140);

  // servo_left.write(180);
  // delay(15);
  // Serial.println(angle);
  // servo_right.write(0);
  // Serial.println(angle);
  
  dcv_control();
  delay(500);

  rollers();
  // delay(2000);

  // dcv_control();
  // delay(400);

  //stoprollers();

  // VL53L0X_RangingMeasurementData_t measure;

  // Serial.print("Reading a measurement... ");
  // lox.rangingTest(&measure, false); 

  // if (measure.RangeStatus != 4){ 
  //   Serial.print("Distance (mm): ");
  //   Serial.println(measure.RangeMilliMeter);

  //   if(measure.RangeMilliMeter==750){
  //     Serial.println("tof reading");
  //   }
  // }
  // else {
  //   Serial.println(" out of range ");
  // }
  // digitalWrite(piston1,LOW);
  // digitalWrite(piston2,HIGH);
  // delay(5000);
  // digitalWrite(piston1,LOW);
  // digitalWrite(piston2,LOW);
  // delay(5000);
  // digitalWrite(piston1,HIGH);
  // digitalWrite(piston2,LOW);
  // delay(1000);


  //delay(750);
  // digitalWrite(piston1,LOW);
  // digitalWrite(piston2,HIGH);
  // delay(1000);
  // // digitalWrite(piston1,LOW);
  // // digitalWrite(piston2,LOW);
  // // delay(500);
  // digitalWrite(piston1,HIGH);
  // digitalWrite(piston2,LOW);
  // delay(1000);
  // digitalWrite(piston1,HIGH);
  // digitalWrite(piston2,HIGH);



  
}
void loop(){

}
