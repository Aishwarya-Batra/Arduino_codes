int piston1=16;
int piston2=17;
void setup(){

  pinMode(piston1,OUTPUT);
  pinMode(piston2,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  digitalWrite(piston1,HIGH);
  digitalWrite(piston2,HIGH);

  delay(3000);
  digitalWrite(piston1,LOW);
  digitalWrite(piston2,HIGH);
  delay(2000);
  // digitalWrite(piston1,LOW);
  // digitalWrite(piston2,LOW);
  // delay(2000);
  digitalWrite(piston1,HIGH);
  digitalWrite(piston2,LOW);
  delay(2000);



}
void loop(){

}

