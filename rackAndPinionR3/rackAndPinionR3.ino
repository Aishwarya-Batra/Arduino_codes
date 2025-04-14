dribble_arm_dir=10;
dribble_arm_pwm=11;
int value=0;
int drb_flag_l=0;
int drb_flag_r=0;

int drb_arm[4]={}; //l-in l-out r-in r-out
bool drb_limit[4]={0,1}

void dribbling_arm(){
  if(drb_flag_l==0 && drb_flag_r==0){
    if(buttons==4){
      digitalWrite(dribble_arm_dir,HIGH);
      analogWrite(dribble_arm_pwm,255*64);

    }
    else if(drb_limit[1]==0 && drb_limit[3]==0){
      digitalWrite(dribble_arm_dir,LOW);
      analogWrite(dribble_arm_pwm,0);
      drb_flag_l=1;
      drb_flg_r=1;
    }
  }

  else if(drb_flag_l==1 && drb_flag_r==1){
    if(button==4){
      digitalWrite(dribble_arm_dir,HIGH);
      analogWrite(dribble_arm_pwm,255*64);
    }
    else if(drb_limit[0]==0 && drb_limit[2]==0){
      digitalWrite(dribble_arm_dir,LOW);
      analogWrite(dribble_arm_pwm,0);
      drb_flag_l=0;
      drb_flg_r=1;

    }
  }
  

}


void setup(){
  Serial.begin(9600);
    
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  analogWriteResolution(14);
  analogWriteFrequency(motor_pwm_pin,9000);

  for(int i=0;i<4;i++){
    pinMode(drb_arm[i],INPUT_PULLUP);
  }

  pinMode(dribble_arm_dir,OUTPUT);
  pinMode(dribble_arm_pwm,OUTPUT);
  digitalWrite(dribble_arm_dir,LOW);
  analogWrite(dribble_arm_pwm,0);

}
void loop(){
  if (Serial.available() > 0) {  // Check if data is available
        String input = Serial.readStringUntil('\n');  // Read input
        input.trim();  // Remove any whitespace
        value = input.toInt();  // Convert the entire string to an integer

    }              
    Serial.println(value);
    
}