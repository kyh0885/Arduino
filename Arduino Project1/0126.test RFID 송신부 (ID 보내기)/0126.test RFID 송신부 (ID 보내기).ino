#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>

SoftwareSerial P_Serial(6,7);

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN); 
MFRC522::MIFARE_Key key; 

byte nuidPICC[4]; //카드 ID들을 저장하기 위한 배열선언
void setup() 
{ 
  //Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  P_Serial.begin(9600);
  rfid.PCD_Init(); // Init MFRC522 
}
 
void loop() 
{
  if ( ! rfid.PICC_IsNewCardPresent() || ! rfid.PICC_ReadCardSerial()) 
  {
     delay(500);
     return;
  }
  
  //Serial.print("Card UID: ");

  for(byte i = 0; i < 4; i++)
  {
    //Serial.print(rfid.uid.uidByte[i]);
    //Serial.print(" ");
    rfid.uid.uidByte[i];
  }
  //Serial.println();
  

  String str = (String)rfid.uid.uidByte[0] + "#" +(String)rfid.uid.uidByte[1]+ "#"+ (String)rfid.uid.uidByte[2]+ "#" + (String)rfid.uid.uidByte[3];
  //Serial.println(str);
  P_Serial.println(str);
}


 