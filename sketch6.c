#include "MFRC522.h"
#include "SPI.h"

MFRC522 rfid(10,9);
//MFRC522::MIFARE_Key key;

void setup() {
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(A5, OUTPUT);  
SPI.begin();
rfid.PCD_Init();
digitalWrite(3, HIGH);
digitalWrite(2, HIGH);
Serial.begin(9600);
}

void loop() {
  if(rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()){
    for(int i = 0 ;i < 4; i++){
      Serial.print(rfid.uid.uidByte[i]);
    }
    Serial.print("\n");
    if(rfid.uid.uidByte[0] == 218){
      tone(A5, 1000, 500);
      digitalWrite(3, LOW);
      delay(1000);
      digitalWrite(3, HIGH);
    }
    else{
      tone(A5, 100, 500);
      digitalWrite(2, LOW);
      delay(1000);
      digitalWrite(2, HIGH);
    }
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}
