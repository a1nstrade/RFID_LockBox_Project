#include <LiquidCrystal.h>

// LCD connections:
// RS = 8
// E  = 11
// D4 = 5
// D5 = 4
// D6 = 3
// D7 = 2

LiquidCrystal lcd(8, 11, 4, 5, 6, 7);

void setupLCD() {
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("RFID Lockbox");

  lcd.setCursor(0, 1);
  lcd.print("Scan Your Card");
}

void updateLCD() {
}
