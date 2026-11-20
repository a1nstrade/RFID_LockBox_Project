#include <SPI.h>
#include <MFRC522.h>

//MFRC522 wiring
#define SS_PIN 10
#define RST_PIN 9

//Create the RFID reader object
MFRC522 rfid(SS_PIN, RST_PIN);

//The AUTHORIZED Card
const byte authorizedUID[] = {
  0x5A, 0x74, 0x17, 0xA5
};

//Initialize the RFID reader
void setupRFID() {
  SPI.begin();
  rfid.PCD_Init();
  delay(4);
  Serial.println("RFID Reader Ready.");
}

//Detect and read a card/tag
bool readCard() {
  //RFID card nearby?
  if (!rfid.PICC_IsNewCardPresent()) {
    return false;
  }
  //Read the card's UID
  if (!rfid.PICC_ReadCardSerial()) {
    return false;
  }
  Serial.print("Scanned UID: ");
  //Print each UID byte
  for (byte i = 0; i < rfid.uid.size; i++) {

    if (rfid.uid.uidByte[i] < 0x10) {
      Serial.print("0");
    }
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  return true;
}

//Check if card is authorized
bool isAuthorized() {
  //UID must have the same length
  if (rfid.uid.size != sizeof(authorizedUID)) {
    return false;
  }
  //Compare every UID byte
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] != authorizedUID[i]) {
      return false;
    }
  }
  //All bytes matched
  return true;
}
// End communication with card
void finishCard() {
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
