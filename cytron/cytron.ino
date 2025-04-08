int roller1_pin1=21;
int roller1_spd=23;

int roller2_pin1=20;
int roller2_spd=22;

void rollers(){
 digitalWrite(roller1_pin1,HIGH);
 analogWrite(roller1_spd,160);

 digitalWrite(roller2_pin1,LOW);
 analogWrite(roller2_spd,160); 

}

void stoprollers(){
 digitalWrite(roller1_pin1,LOW);
 analogWrite(roller1_spd,0);

 digitalWrite(roller2_pin1,LOW);
 analogWrite(roller2_spd,0); 


}

void setup(){
  pinMode(roller1_pin1, OUTPUT);
  //pinMode(rollor1_pin2, OUTPUT);
  pinMode(roller1_spd, OUTPUT);

  pinMode(roller2_pin1, OUTPUT);
  //pinMode(rollor2_pin2, OUTPUT);
  pinMode(roller2_spd, OUTPUT);
  
  stoprollers();

}
void loop(){
  //rollers();
  //delay(5000);
  stoprollers();
  //delay(5000);
}
