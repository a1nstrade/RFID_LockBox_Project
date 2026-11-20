
#include <LiquidCrystal.h>

// LCD wiring:
// RS = 8
// E  = A0
// D4 = 4
// D5 = 5
// D6 = 6
// D7 = 7

LiquidCrystal lcd(8, A0, 4, 5, 6, 7);

// Initialize LCD
void setupLCD() {

  lcd.begin(16, 2);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("RFID Lockbox");

  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
}

// Display a two-line message
void displayMessage(const char* line1,
                    const char* line2) {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(line1);

  lcd.setCursor(0, 1);
  lcd.print(line2);
}

// Display ready screen
void displayReady() {
  displayMessage("RFID Lockbox",
                 "Scan Your Card");
}
