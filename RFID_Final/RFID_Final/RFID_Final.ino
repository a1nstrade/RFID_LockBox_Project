
#include <SPI.h>
#include <MFRC522.h>

// RFID reader pins
#define SS_PIN 10
#define RST_PIN 9

// Create MFRC522 object
void setup() {

  Serial.begin(9600);

  SPI.begin();
  rfid.PCD_Init();

  Serial.println("RFID Reader Ready!");
  Serial.println("Scan your card or tag...");
}

void loop() {

  // Check if a new card is present
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Read the card UID
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("Scanned UID: ");

  // Print every byte of the UID
  for (byte i = 0; i < rfid.uid.size; i++) {

    if (rfid.uid.uidByte[i] < 0x10) {
      Serial.print("0");
    }

    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }

  Serial.println();

  // Finish communication with the card
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(500);
}
