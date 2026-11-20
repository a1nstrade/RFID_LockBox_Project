
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

//Servo motor signal pin
#define SERVO_PIN A1

//Angles used for the locking mechanism
const int LOCKED_ANGLE = 0;
const int UNLOCKED_ANGLE = 90;

//Function to keep box unlocked for 5 seconds
const unsigned long UNLOCK_TIME = 5000;

//Create servo motor object
Servo lockServo;

//Track whether box is unlocked or not
bool boxUnlocked = false;

//Track when unlocking started
unsigned long unlockStartTime = 0;

//RFID functions
void setupRFID();
bool readCard();
bool isAuthorized();
void finishCard();

//Function to initialize servo motor
void setupServo() {
  lockServo.attach(SERVO_PIN);
  //Start the servo in the locked position
  lockServo.write(LOCKED_ANGLE);
  Serial.println("Servo Motor Ready");
}

//Function to unlock the box
void unlockBox() {
  Serial.println("ACCESS GRANTED");
  Serial.println("Unlocking Box...");
  //Rotate servo to unlocked position
  lockServo.write(UNLOCKED_ANGLE);
  //Record when box was unlocked
  unlockStartTime = millis();
  boxUnlocked = true;
}

//Lock the box
void lockBox() {
  //Rotate servo back to its locked position
  lockServo.write(LOCKED_ANGLE);
  boxUnlocked = false;
  Serial.println("Box Locked.");
  Serial.println("Scan your card or tag...");
}

//SETUP: Runs once at startup
void setup() {
  Serial.begin(9600);
  setupRFID();
  setupServo();
  Serial.println("RFID Lock Box Ready.");
  Serial.println("Scan your card or tag...");
}

//LOOP: Runs continuously
void loop() {
  //If unlocked, check whether 5 seconds have passed
  if (boxUnlocked) {
    if (millis() - unlockStartTime >= UNLOCK_TIME) {
      lockBox();
    }
    return;
  }
  //1) Detect a card or tag
  if (!readCard()) {
    return;
  }
  //2) Verify the UID with the internalized UID
  bool authorized = isAuthorized();
  //3) End RFID communication
  finishCard();
  //4) Decide based on input recieved from RFID Reader
  if (authorized) {
    unlockBox();
  } else {
    Serial.println("ACCESS DENIED");
    Serial.println("Box remains locked!");
  }
  Serial.println("----------------");
}
