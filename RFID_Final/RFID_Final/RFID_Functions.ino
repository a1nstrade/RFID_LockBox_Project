#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

void setupRFID(){
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("RFID Reader Ready.");
}