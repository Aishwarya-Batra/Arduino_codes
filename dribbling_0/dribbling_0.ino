#include <Servo.h>
#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Servo s;
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

int roller1_pin1 =;
//int roller1_pin2 =;
int roller1_spd =;

int roller2_pin1 =;
//int roller2_pin2 =;
int roller2_spd =;

int onpin =;
int ofpin =;

int piston1=;
int piston2=;

float easeInOutQuint(float x) {
  return (x < 0.5) ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2;
}

void servomotion(int startPos, int endPos, int duration) {
  int steps = 100;
  for (int i = 0; i <= steps; i++) {
    float progress = (float)i / steps;
    float easedProgress = easeInOutQuint(progress);
    int servoPos = startPos + (endPos - startPos) * easedProgress;
    s.write(servoPos);
    delay(duration / steps);
  }
}

void rollors() {
  digitalWrite(roller1_pin1, HIGH);
  //digitalWrite(roller1_pin2, LOW);
  analogWrite(roller1_spd, 255);

  digitalWrite(roller2_pin1, HIGH);
  //digitalWrite(roller2_pin2, LOW);
  analogWrite(roller2_spd, 255);
}

void stoprollors() {
  digitalWrite(roller1_pin1, LOW);
  //digitalWrite(roller1_pin2, LOW);
  analogWrite(roller1_spd, 0);

  digitalWrite(roller2_pin1, LOW);
  //digitalWrite(roller2_pin2, LOW);
  analogWrite(roller2_spd, 0);
}

void dcv_control() {
  digitalWrite(onpin, HIGH);
  digitalWrite(ofpin, LOW);
  delay(100);
}

void setup() {
  Serial.begin(115200);
  s.attach(9);

  // Initialize pins
  pinMode(onpin, OUTPUT);
  pinMode(ofpin, OUTPUT);

  pinMode(piston1,OUTPUT);
  pinMode(piston2,OUTPUT);

  pinMode(roller1_pin1, OUTPUT);
  //pinMode(roller1_pin2, OUTPUT);
  pinMode(roller1_spd, OUTPUT);

  pinMode(roller2_pin1, OUTPUT);
  //pinMode(roller2_pin2, OUTPUT);
  pinMode(roller2_spd, OUTPUT);

  stoprollors();

  // Initialize the sensor
  Wire.begin();
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1)
      ;
  }
}

void loop() {
  
  rollors();
  delay(300);
  stoprollors();

  //dcv ball push code


  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) {
    Serial.print("Distance (mm): ");
    Serial.println(measure.RangeMilliMeter);

    if (measure.RangeMilliMeter==) {
      digitalWrite(piston1,HIGH);
      digitalWrite(piston2,HIGH);
      delay(500);
      digitalWrite(piston1,LOW);
      digitalWrite(piston2,LOW);
    }
  } else {
    Serial.println("Out of range");
  }

  delay(100);
}
