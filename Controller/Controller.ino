// Simple example application that shows how to read four Arduino
// digital pins and map them to the USB Joystick library.
//
// The digital pins 9, 10, 11, and 12 are grounded when they are pressed.
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// by Matthew Heironimus
// 2015-11-20
//--------------------------------------------------------------------

#include "Joystick.h"

// Create the Joystick
// Joystick_ Joystick;
Joystick_ Joystick(
  JOYSTICK_DEFAULT_REPORT_ID, // Reports Joystick HID
  JOYSTICK_TYPE_JOYSTICK, // Joystick Type
  6, // Number of Buttons
  0, // Number of Hat Switches
  false, // X-Axis Available
  false, // Y-Axis Available
  true, // Z-Axis Available
  false, // X-Rotational-Axis Available
  false, // Y-Rotational-Axis Available
  false, // Z-Rotational-Axis Available
  false, // Rudder Available
  false, // Throttle Available
  false, // Accelerator Available
  false, // Break Available
  false // Steering Available
);

void setup() {
  // Initialize Button Pins
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.begin();
}

// Constant that maps the phyical pin to the joystick button.
const int pinToButtonMap = 8;

// Last state of the button
int lastButtonState[6] = {0,0,0,0,0,0};

void loop() {

  // Read pin values
  for (int index = 0; index < 5; index++)
  {
    int currentButtonState = !digitalRead(index + pinToButtonMap);
    if (currentButtonState != lastButtonState[index])

    // Code for Momentary Switch
    {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }

    // Code for Toggle Switches
    // {
    //   Joystick.pressButton(index);
    //   delay(50);
    //   Joystick.releaseButton(index);
    //   lastButtonState[index] = currentButtonState;
    // }
  }

  // Reads the value of pin A0 -- Range 0 - 1023
  int sensorValue = analogRead(A0);
  // Inverts value of pin A0 to change direction
  int raw = (sensorValue - 1023) * -1;
  // Sets throttle to value
  Joystick.setZAxis(raw);

  // switch (lastButtonState[5]) {
  //   case 0:
  //     if (raw <= 50 && lastButtonState[5] == 0) {
  //       Joystick.pressButton(5);
  //       delay(150);
  //       Joystick.releaseButton(5);
  //       lastButtonState[5] = 1;
  //     }
  //     if (raw >= 950 && lastButtonState[5] == 0) {
  //       Joystick.pressButton(5);
  //       delay(150);
  //       Joystick.releaseButton(5);
  //       lastButtonState[5] = 1;
  //     }
  //     break;

  //   case 1:
  //     if (raw >= 50 && raw <= 950) {
  //       lastButtonState[5] = 0;
  //     }
  //     break;
  // }

  delay(50);
}
