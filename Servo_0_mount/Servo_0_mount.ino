#include<Servo.h>
Servo s;

void setup(){
  Serial.begin(9600);
  s.attach(3);

}
int value=0;
void loop(){
  if (Serial.available() > 0) {  // Check if data is available
        String input = Serial.readStringUntil('\n');  // Read input
        input.trim();  // Remove any whitespace
        value = input.toInt();  // Convert the entire string to an integer

    }              
    Serial.println(value);
    s.write(value);

}