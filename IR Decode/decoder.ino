// Michael duBois
// 2019.12.27
#include "IRremote.h"
#include <LiquidCrystal.h>

// Setup Receiver Pins
int receiver = 2;
// Delcare Objects
IRrecv irrecv(receiver);
decode_results results;

// Setup LCD
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
int powerPin = 4;

void setup() {
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);

  // Define LCD Size
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.write("Received:");

  // Start IR Receiver
  irrecv.enableIRIn();
}

void loop() {
  // IR Signal
  if (irrecv.decode(&results)) {
    // Decode IR
    decodeIR();

    // Resume Receiver
    irrecv.resume();
  }
}

void triggerDelay() {
  delay(250);
}

void decodeIR() {
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(results.value);
  triggerDelay();
}