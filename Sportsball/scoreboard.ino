// Michael duBois
// 2019.12.26
#include <LiquidCrystal.h>

// Setup Button Pins
int addOne = 2;
int addTwo = 3;
int addThree = 4;
int addSix = 5;
int selectTeam = 6;

// Setup teamSelect
bool teamSelect = false;

// Score Setup
int awayScore = 0;
int homeScore = 0;

// Setup LCD wiht Pins on Uno
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Setup Pin Types
void setup() {
  lcd.begin(16, 2);
  pinMode(addOne, INPUT_PULLUP);
  pinMode(addTwo, INPUT_PULLUP);
  pinMode(addThree, INPUT_PULLUP);
  pinMode(addSix, INPUT_PULLUP);
  pinMode(selectTeam, INPUT_PULLUP);

  // Setup Away Team
  lcd.setCursor(2, 0);
  lcd.print("AWAY: ");

  // Setup Home Team
  lcd.setCursor(2, 1);
  lcd.print("HOME: ");
}

void loop() {
  // Away Score Display
  lcd.setCursor(8, 0);
  lcd.print((int)awayScore);

  // Home Score Display
  lcd.setCursor(8, 1);
  lcd.print((int)homeScore);

  // Team Selection
  if (digitalRead(selectTeam) == LOW) {
    teamSelect = !teamSelect;
  }

  // Team Display Adjustments
  switch (teamSelect) {
    case false:
      lcd.setCursor(0, 0);
      lcd.print("*");
      lcd.setCursor(0, 1);
      lcd.print(" ");
      if (digitalRead(addOne) == LOW) {
        awayScore += 1;
      }
      if (digitalRead(addTwo) == LOW) {
        awayScore += 2;
      }
      if (digitalRead(addThree) == LOW) {
        awayScore += 3;
      }
      if (digitalRead(addSix) == LOW) {
        awayScore += 6;
      }
      break;

    case true:
      lcd.setCursor(0, 0);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("*");
      if (digitalRead(addOne) == LOW) {
        homeScore += 1;
      }
      if (digitalRead(addTwo) == LOW) {
        homeScore += 2;
      }
      if (digitalRead(addThree) == LOW) {
        homeScore += 3;
      }
      if (digitalRead(addSix) == LOW) {
        homeScore += 6;
      }
      break;
  }

  // Trigger Delay
  delay(500);
}