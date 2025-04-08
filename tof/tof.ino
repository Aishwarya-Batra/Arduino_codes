#include <Wire.h>

#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

 


void setup() {
  Wire.begin(); //default sda and scl 18 19
  Serial.begin(115200);
  // wait until serial port opens for native USB devices
  while (!Serial) {
    delay(1);
  }

  //Initialize the sensor
  Serial.println("Adafruit VL53L0X test");
  delay(100);
  Serial.println("---");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1)  //Stop the program if the sensor cannot be initialized
      ;
  }
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); 

  if (measure.RangeStatus != 4){ 
    Serial.print("Distance (mm): ");
    Serial.println(measure.RangeMilliMeter);
  }
  else {
    Serial.println(" out of range ");
  }

  delay(100);
}
