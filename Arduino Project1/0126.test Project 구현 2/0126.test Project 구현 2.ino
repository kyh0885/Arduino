#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <MFRC522.h>

#define SS_PIN 10  //RFID
#define RST_PIN 9

SoftwareSerial P_Serial(2, 3);

char data;                           //LCD 문자
LiquidCrystal_I2C lcd(0x27, 16, 2);  //LCD 문자

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

byte nuidPICC[4];  // RFID ID을 알아내기위한 배열 선언

void setup() 
{
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  P_Serial.begin(9600);

  SPI.begin();      // Init SPI bus
  rfid.PCD_Init();  // Init MFRC522
}

void loop() 
{
 
}
