#include <LiquidCrystal.h>

// ==================================================
// LCD DISPLAY
// ==================================================

// RS = 1, E = 2, D4 = 4, D5 = 5, D6 = 6, D7 = 7
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

void setupLCD() {
  // Initialize the LCD (16 columns, 2 rows)
  lcd.begin(16, 2);

  // Display message
  lcd.setCursor(0, 0);
  lcd.print("Hello World!");
}

// ==================================================
// FUTURE LCD FUNCTIONS
// ==================================================

// Show access granted message


// Show access denied message


// Show other status messages

