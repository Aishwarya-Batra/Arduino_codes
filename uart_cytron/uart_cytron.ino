#include "USBHost_t36.h"

/* 
 * This example shows how to control MDDS30 in Serial Simplified mode with Arduino.
 * Set MDDS30 input mode to 0b11001100
 * Open Serial Monitor, set baudrate to 9600bps and "No line ending".
 * Send 0: Left motor stops
 *      1: Left motor rotates CW with half speed
 *      2: Left motor rotates CW with full speed
 *      3: Left motor rotates CCW with half speed
 *      4: Left motor rotates CCW with full speed
 *      5: Right motor stops
 *      6: Right motor rotates CW with half speed
 *      7: Right motor rotates CW with full speed
 *      8: Right motor rotates CCW with half speed
 *      9: Right motor rotates CCW with full speed
 * 
 * Note: This example also compatible with MDDS10 and MDDS60
 *
 * Hardware Connection:
 *   Arduino Uno    MDDS30
 *   GND ---------- GND
 *   4 ------------ IN1
 *
 * Related Products:
 * - SmartDriveDuo-30: http://www.cytron.com.my/P-MDDS60
 * - CT UNO: http://www.cytron.com.my/p-ct-uno
 * - DC Brush Motors: http://www.cytron.com.my/c-84-dc-motor
 * - LiPo Battery: http://www.cytron.com.my/c-87-power/c-97-lipo-rechargeable-battery-and-charger
 * - Male to Male Jumper: https://www.cytron.com.my/p-wr-jw-mm65
 *
 * URL: http://www.cytron.com.my
 */

#include <SoftwareSerial.h>
#include <Cytron_SmartDriveDuo.h>
#define IN1 1 // Arduino pin 4 is connected to MDDS60 pin IN1.
#define BAUDRATE  9600
Cytron_SmartDriveDuo smartDriveDuo30(SERIAL_SIMPLIFIED, IN1, BAUDRATE);

//PS4 connection 
USBHost myusb;   // initializes and manages the USB host port, enabling Teensy to detect and commuincate with USB bluetooth dongle
USBHIDParser hid1(myusb);  //works behind the scenes to parse HID data that comes from the PS4 controller, such as joystick movements and button presses.
JoystickController joystick(myusb);
BluetoothController bluet(myusb, true, "0000"); 
//BluetoothController bluet(myusb);   // Version does pairing to device

char inChar;
signed int speedLeft, speedRight;
int x, y;

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
  digitalWrite(13, HIGH);
  delay(2000); // Delay for 5 seconds.
  digitalWrite(13, LOW);

  Serial.println("\n\nUSB Host Testing - Joystick Bluetooth");
  if (CrashReport) Serial.print(CrashReport);
  myusb.begin();
  myusb.Task();
}

void loop()
{

  myusb.Task();   // Handle USB host tasks

  if (joystick.available()) {
    // if(joystick.getButtons()){
    //   // Serial.println("value");

    // }

    // Right Stick values (axes 2 and 5)
    int rightStickX = joystick.getAxis(2);
    x = map(rightStickX, 0, 255, -100, 100);

    int rightStickY = joystick.getAxis(5);
    y = map(rightStickY, 0, 255, 100, -100);

    smartDriveDuo30.control(x, y);

  if (Serial.available()) {
    delay(100);
    inChar = (char)Serial.read();

    if (inChar == '0') {
      digitalWrite(13, LOW);
      speedLeft = 0;
      Serial.println(speedLeft);
    }
    else if (inChar == '1') {
      digitalWrite(13, HIGH);
      speedLeft = 50;
      Serial.println(speedLeft);
    }
    else if (inChar == '2') {
      digitalWrite(13, HIGH);
      speedLeft = 100;
      Serial.println(speedLeft);
    }
    else if (inChar == '3') {
      digitalWrite(13, HIGH);
      speedLeft = -50;
      Serial.println(speedLeft);
    }
    else if (inChar == '4') {
      digitalWrite(13, HIGH);
      speedLeft = -100;
      Serial.println(speedLeft);
    }
    else if (inChar == '5') {
      digitalWrite(13, LOW);
      speedRight = 0;
      Serial.println(speedRight);
    }
    else if (inChar == '6') {
      digitalWrite(13, HIGH);
      speedRight = 50;
      Serial.println(speedRight);
    }
    else if (inChar == '7') {
      digitalWrite(13, HIGH);
      speedRight = 100;
      Serial.println(speedRight);
    }
    else if (inChar == '8') {
      digitalWrite(13, HIGH);
      speedRight = -50;
      Serial.println(speedRight);
    }
    else if (inChar == '9') {
      digitalWrite(13, HIGH);
      speedRight = -100;
      Serial.println(speedRight);
    }

  } 
  
}