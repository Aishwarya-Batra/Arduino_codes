int dir_pin;
int step_pin;

char values="";
char revolution="";
char direction='';
char dl="";

void setup(){
  Serial.begin(9600); //bits per second
  pinMode(dir_pin,OUTPUT);
  pinMode(step_pin,OUTPUT);
  Serial.println("enter the values in a form of single string:");

}

void loop(){
  if(Serial.available()>0){
    values=Serial.readString();
    revolution=values.substring(0,2).toint();
    direction=values.substring(2,3);
    speed=values.substring(3).toint();
    
    Serial.println("REVOLUTION:");
    Serial.print(revolution);

    Serial.println("DIRECTION:");
    Serial.print(direction);

    Serial.println("SPEED:")
    Serial.print(dl); 

    if(direction[2]=='f'){
      digitalWrite(dir_pin,HIGH);
      for(int i;i<=200;i++){
        digitalWrite(step_pin,HIGH);
        delay(dl);
        digitalWrite(step_pin,LOW);
        delay(dl);
      }
    }
    else if(direction[2]=='b'){
      digitalWrite(dir_pin,LOW);
      for(int j;j<=200;j++){
        digitalWrite(step_pin,HIGH);
        delay(dl);
        digitalWrite(step_pin,LOW);
        delay(dl);
      }
    }
  }
}