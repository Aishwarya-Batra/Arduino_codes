
int on=16;
int of=17;

int piston1=19;
int piston2=18;

void dcv_control(){
  digitalWrite(on,LOW);
  digitalWrite(of,HIGH);
  delay(500);

  digitalWrite(on,LOW);
  digitalWrite(of,LOW);
  delay(300);

  digitalWrite(of,LOW);
  digitalWrite(on,HIGH); 
}

void setup(){
  
  //pinMode(on,OUTPUT);
  //pinMode(of,OUTPUT);

  // digitalWrite(on,HIGH);
  // digitalWrite(of,HIGH);
  // delay(100);

  pinMode(piston1,OUTPUT);
  pinMode(piston2,OUTPUT);
  
  digitalWrite(piston1,HIGH);
  digitalWrite(piston2,HIGH);
  delay(100);

  //dcv_control();
  //delay(200);

  digitalWrite(piston1,LOW);
  digitalWrite(piston2,HIGH);
  delay(5000);
  digitalWrite(piston1,LOW);
  digitalWrite(piston2,LOW);
  delay(5000);
  digitalWrite(piston1,HIGH);
  digitalWrite(piston2,LOW);
  delay(10000);


}

void loop(){




  // digitalWrite(piston1,HIGH);
  // digitalWrite(piston2,LOW);
  // delay(5000);
  // digitalWrite(piston1,LOW);
  // digitalWrite(piston2,LOW);
  // delay(5000);
  // digitalWrite(piston1,LOW);
  // digitalWrite(piston2,HIGH);

}

    
