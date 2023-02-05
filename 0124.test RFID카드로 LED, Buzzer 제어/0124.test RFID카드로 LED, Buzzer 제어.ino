/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read new NUID from a PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * Example sketch/program showing how to the read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
 * Reader on the Arduino SPI interface.
 * 
 * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
 * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
 * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
 * will show the type, and the NUID if a new card has been detected. Note: you may see "Timeout in communication" messages
 * when removing the PICC from reading distance too early.
 * 
 * @license Released into the public domain.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

int LED = 2;
int sensor = 7;
int value = 0;
int buzzerPin = 3;

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4]; //카드 ID들을 저장하기 위한 배열선언

void setup() 
  {
  Serial.begin(9600);
  SPI.begin(); // SPI통신 시작
  rfid.PCD_Init(); // Init MFRC522 초기화

  pinMode(LED, OUTPUT); //핀모드 LED 출력으로 설정
  pinMode(buzzerPin, OUTPUT); // 핀모드 buzzerPin 출력으로 설정
  pinMode(sensor, INPUT); // 핀모드 센서 입력값으로 설정

  /*for (byte i = 0; i < 6; i++) 
  {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("This code scan the MIFARE Classsic NUID.")); 
  Serial.print(F("Using the following key:"));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE); *///4Byte 배열로 읽히는 RFID 정보를 Hex(16진수)로 출력
}
 
void loop() {

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  /*if ( ! rfid.PICC_IsNewCardPresent()) //새 카드가 읽히면 다음으로 넘어감
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial()) //카드읽힘이 제대로 되면 다음으로 넘어감
    return;*/
  
  if ( ! rfid.PICC_IsNewCardPresent() || ! rfid.PICC_ReadCardSerial() ) //카드가 접촉이 안되었을때
  {
    delay(500);
    return;
  }
  if(rfid.uid.uidByte[0] == 229 && rfid.uid.uidByte[1] == 114 
     && rfid.uid.uidByte[2] == 18 && rfid.uid.uidByte[3] == 173){
      digitalWrite(LED,HIGH); //LED를 켜라
      delay(1000);
      digitalWrite(LED,LOW);
      delay(1000);
      Serial.println("Hello, yuni");

      tone(buzzerPin, 131); //수동 부저 설정방법(능동부저랑 설정방법이 다르므로 주의)
      delay(1000);
      noTone(buzzerPin);
      delay(1000);
  
      tone(buzzerPin, 262);
      delay(1000);
      noTone(buzzerPin);
      delay(1000);
     }
  else // 다른 아이디의 카드가 테그가 되었다면
  {
    digitalWrite(LED,HIGH); //LED를 켜라
    delay(3000);
    digitalWrite(LED,LOW); 
    delay(3000);
    Serial.println("Who are you?");
  }  
}
  /*Serial.print(F("PICC type: ")); //카드 타입을 읽어서 출력 (PICC??)
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type 타입체크
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
   
    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    Serial.print(F("In dec: ")); // Dex는 10진값으로 출력하기 위함
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
  }
  else Serial.println(F("Card read previously."));

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}*/


/* 여기 아래는 Hex, Dex 로 변환해주는 함수들
 * Helper routine to dump a byte array as hex values to Serial. 
 
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}*/
