#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h> 

#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc (SS_PIN, RST_PIN); 

void setup() 
{
 Serial.begin(9600);
 SPI.begin();
 mfrc.PCD_Init();
}

void loop() 
{
 if(! mfrc.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if(! mfrc.PICC_ReadCardSerial())
  {
    return;
  }
  if(mfrc.uid.uidByte[0] == 229 &&
     mfrc.uid.uidByte[1] == 114 &&
     mfrc.uid.uidByte[2] == 18 &&
     mfrc.uid.uidByte[3] == 173)
  {
    Serial.println("Hello");
    delay(500);
  }
  else
  {
    Serial.println("Bye");
    delay(500);
  }
  
 /* Serial.print("Card UID : ");
  for (byte i=0; i<4; i++)
  {
    Serial.print(mfrc.uid.uidByte[i]);
    Serial.print(" ");
  }
    Serial.println();
    delay(50);*/
}


