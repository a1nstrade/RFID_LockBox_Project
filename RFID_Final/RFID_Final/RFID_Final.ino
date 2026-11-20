
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// Servo motor signal pin
#define SERVO_PIN A1

// Angles used for the locking mechanism
const int LOCKED_ANGLE = 0;
const int UNLOCKED_ANGLE = 90;

// Keep the box unlocked for 5 seconds
const unsigned long UNLOCK_TIME = 5000;

// Create servo motor object
Servo lockServo;

// Track whether box is unlocked
bool boxUnlocked = false;

// Track when unlocking started
unsigned long unlockStartTime = 0;

// RFID functions from RFID_Functions.ino
void setupRFID();
bool readCard();
bool isAuthorized();
void finishCard();

// LCD functions from LCD_Display.ino
void setupLCD();
void displayReady();
void displayMessage(const char* line1, const char* line2);

// Initialize servo motor

void setupServo() {

  lockServo.attach(SERVO_PIN);

  // Start the servo in the locked position
  lockServo.write(LOCKED_ANGLE);

  Serial.println("Servo Motor Ready");
}

// Unlock the box

void unlockBox() {

  Serial.println("ACCESS GRANTED");
  Serial.println("Unlocking Box...");

  // Rotate servo to unlocked position
  lockServo.write(UNLOCKED_ANGLE);

  // Record when the box was unlocked
  unlockStartTime = millis();

  boxUnlocked = true;
}


// Lock the box

void lockBox() {

  // Rotate servo to locked position
  lockServo.write(LOCKED_ANGLE);

  // Update box status
  boxUnlocked = false;

  Serial.println("Box Locked.");
  Serial.println("Scan your card or tag...");

  // Update the LCD display
  displayMessage("BOX LOCKED",
                 "Scan Your Card");
}

// SETUP: Runs once at startup

void setup() {

  Serial.begin(9600);

  // Initialize RFID reader
  setupRFID();

  // Initialize servo motor
  setupServo();

  // Initialize LCD
  setupLCD();

  // Display ready message
  displayReady();

  Serial.println("RFID Lock Box Ready.");
  Serial.println("Scan your card or tag...");
}


// -----------------------------------
// LOOP: Runs continuously
// -----------------------------------

void loop() {

  // If the box is unlocked, check
  // whether 5 seconds have passed
  if (boxUnlocked) {

    if (millis() - unlockStartTime >= UNLOCK_TIME) {
      lockBox();
    }

    // Do not read cards while unlocked
    return;
  }

  // Step 1: Detect a card or tag
  if (!readCard()) {
    return;
  }

  // Step 2: Check UID authorization
  bool authorized = isAuthorized();

  // Step 3: Finish RFID communication
  finishCard();

  // Step 4: Decide whether to unlock
  if (authorized) {

    // White card is authorized
    displayMessage("ACCESS GRANTED",
                   "Box Unlocked");

    unlockBox();

  } else {

    // Unauthorized key tag
    Serial.println("ACCESS DENIED");
    Serial.println("Box remains locked!");

    displayMessage("ACCESS DENIED",
                   "Invalid Card");

    delay(2000);

    displayReady();
  }
}
