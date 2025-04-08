#include "USBHost_t36.h"

bool isJoystick = 0;

//......PS4........
USBHost myusb;
JoystickController joystick1(myusb);
BluetoothController bluet(myusb, true, "0000");   // Version does pairing to device
// BluetoothController bluet(myusb);  // version assumes it already was paireduint32_t buttons_prev = 0;
uint32_t buttons;

int psAxis[64];
int psAxis_prev[64];
bool first_joystick_message = true;
//.......PS4........

void setup(){
  Serial.begin(200000);

  UART.setSerialPort(&Serial7);
  Serial.println("\n\nUSB Host Testing - Joystick Bluetooth");
  if (CrashReport) Serial.print(CrashReport);
  myusb.begin();
  myusb.Task();
}

Serial.printf("\n");
  
//....taking values/input from ps4........
  if (isJoystick == true) {
    int psAxisX = 0;
    int psAxisY = 0;
    int w = 0;
    if (psAxis[0] < 125)
      psAxisX = map(psAxis[0], 125, 0, 0, -255);

    else if (psAxis[0] > 135)
      psAxisX = map(psAxis[0], 135, 255, 0, 255);
    else
      psAxisX = 0;

    if (psAxis[1] > 135)
      psAxisY = map(psAxis[1], 135, 255, 0, 255);

    else if (psAxis[1] < 125)
      psAxisY = map(psAxis[1], 125, 0, 0, -255);
    else
      psAxisY = 0;
    if (psAxis[2] > 135)
      w = map(psAxis[2], 135, 255, 0, 255);

    else if (psAxis[2] < 125)
      w = map(psAxis[2], 125, 0, 0, -255);
    else
      w = 0;

    int y = psAxisY;
    int x = psAxisX;

    Serial.print(x);
    Serial.print("   ok ");
    Serial.print(y);
    Serial.println();
    rpm_sp[0] = map(x + w, -175, 175, max_rpm, -max_rpm);
    rpm_sp[1] = map(-0.5 * x - 0.866 * y + w, -175, 175, max_rpm, -max_rpm);
    rpm_sp[2] = map(-0.5 * x + 0.866 * y + w, -175, 175, max_rpm, -max_rpm);

    for (int i = 0; i < 3; i++) {
      Serial.printf("RPM_%d_input:%0.2f  ", i + 1, rpm_sp[i]);
    }
   
  }
//..........ps4................


void loop(){
   if (joystick1.available()) {
    isJoystick = true;
    for (uint8_t i = 0; i < 64; i++) {
      psAxis_prev[i] = psAxis[i];
      psAxis[i] = joystick1.getAxis(i);
    }
    buttons = joystick1.getButtons();
    // Serial.println(buttons);
  } else {
    isJoystick = false;
  }
  
}
