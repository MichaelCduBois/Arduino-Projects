// Michael duBois
// 2019.12.27
#include "IRremote.h"
#include <LiquidCrystal.h>

// Setup Receiver Pins
int receiver = 2;

// Setup teamSelect
bool teamSelect = false;

// Score Setup
int awayScore = 0;
int homeScore = 0;

// Setup Disable
bool disable = true;

// Delcare Objects
IRrecv irrecv(receiver);
decode_results results;

// Setup LCD
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
bool power = false;
int powerPin = 4;

void setup() {
  // Assign Pin Mode
  pinMode(powerPin, OUTPUT);

  // Turns on LCD
  cyclePower();

  // Define LCD Size
  lcd.begin(16, 2);

  // Start IR Receiver
  irrecv.enableIRIn();

  // Score Setup
  resetScores();
}

void loop() {
  // Away Score Display
  lcd.setCursor(8, 0);
  lcd.print((int)awayScore);

  // Home Score Display
  lcd.setCursor(8, 1);
  lcd.print((int)homeScore);

  // IR Signal
  if (irrecv.decode(&results)) {
    // Decode IR
    decodeIR();

    // Resume Receiver
    irrecv.resume();
  }

  // Team Display Adjustments
  switch (teamSelect) {
    // Away Team
    case false:
      lcd.setCursor(0, 0);
      lcd.print("*");
      lcd.setCursor(0, 1);
      lcd.print(" ");
      break;

    // Home Team
    case true:
      lcd.setCursor(0, 0);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("*");
      break;
  }
}

void triggerDelay() {
  delay(250);
}

void resetScores() {
  // Setup Away Team
  lcd.setCursor(0, 0);
  lcd.print("                ");

  // Setup Home Team
  lcd.setCursor(0, 1);
  lcd.print("                ");

  // Reset teamSelect
  teamSelect = false;

  // Reset Score
  awayScore = 0;
  homeScore = 0;

  // Setup Away Team
  lcd.setCursor(0, 0);
  lcd.print("* AWAY: 0");

  // Setup Home Team
  lcd.setCursor(2, 1);
  lcd.print("HOME: 0");
}

void decodeIR() {
  // Check for Disable
  if (disable && results.value == 0xFFA25D) {
    cyclePower();
  } else if (!disable) {
    switch(results.value) {
      case 0xFFA25D: cyclePower(); break;             // POWER      >>  On/Off Screen
      case 0xFFE21D: resetScores(); break;            // FUNC/STOP  >>  Clear Scores
      case 0xFF9867: break;                           // EQ         >>  Undo  -- To be Completed
      case 0xFFE01F: changeTeam(); break;             // DOWN       >>  Switch Teams
      case 0xFF906F: changeTeam(); break;             // UP         >>  Switch Teams
      case 0xFF6897: modifyScore(0); break;           // 0          >>  +0 to Score
      case 0xFF30CF: modifyScore(1); break;           // 1          >>  +1 to Score
      case 0xFF18E7: modifyScore(2); break;           // 2          >>  +2 to Score
      case 0xFF7A85: modifyScore(3); break;           // 3          >>  +3 to Score
      case 0xFF10EF: modifyScore(4); break;           // 4          >>  +4 to Score
      case 0xFF38C7: modifyScore(5); break;           // 5          >>  +5 to Score
      case 0xFF5AA5: modifyScore(6); break;           // 6          >>  +6 to Score
      case 0xFF42BD: modifyScore(7); break;           // 7          >>  +7 to Score
      case 0xFF4AB5: modifyScore(8); break;           // 8          >>  +8 to Score
      case 0xFF52AD: modifyScore(9); break;           // 9          >>  +9 to Score
    }
  }
}

void changeTeam() {
  teamSelect = !teamSelect;
}

void modifyScore(int score) {
  if (teamSelect) {
    homeScore += score;
  } else {
    awayScore += score;
  }
}

void cyclePower() {
  power = !power;
  disable = !disable;
  if (power) {
    digitalWrite(powerPin, HIGH);
    lcd.display();
  } else {
    digitalWrite(powerPin, LOW);
    lcd.noDisplay();
  }
}