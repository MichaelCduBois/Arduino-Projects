// Michael duBois
// 2020-02-27
// Matrix Controller

#include <Keypad.h>
#include <Joystick.h>

// Create the Joystick
Joystick_ Joystick;

const byte ROWS = 3;
const byte COLS = 2;
const int BUTTONS = 5;

char hexaKeys[ROWS][COLS] = {
  {'0', '1'},
  {'2', '3'},
  {'-', '4'}
};

byte rowPins[ROWS] = {7, 6 , 5};
byte colPins[COLS] = {12, 11};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup(){
  Serial.begin(9600);
  Joystick.begin();
}

int lastButtonState[BUTTONS] = {0, 0, 0, 0, 0};

void loop(){

  for (int index = 0; index < BUTTONS; index++) {
    int currentState = customKeypad.
    if (index == customKeypad.getKey() - 48) {
      Serial.println(index);
    }
  }
}
