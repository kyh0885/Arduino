#include <SoftwareSerial.h>     //SPI 통신
#include <MFRC522.h>            // RFID
#include <SPI.h>                // RFID
#include <LiquidCrystal_I2C.h>  //LCD
#include <Wire.h>               //LCD

#define SS_PIN 10  //RFID
#define RST_PIN 9

SoftwareSerial P_Serial(2, 3);

char data;                           //LCD 문자
LiquidCrystal_I2C lcd(0x27, 16, 2);  //LCD 문자

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

byte nuidPICC[4];  // RFID ID을 알아내기위한 배열 선언

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  P_Serial.begin(9600);

  SPI.begin();      // Init SPI bus
  rfid.PCD_Init();  // Init MFRC522
}

void loop() {
  
  //여기부터  LCD 제어/ 출력 관련
  if (P_Serial.available())  //만약 읽을 데이터가 있을 시
  {
    data = P_Serial.read();
  }
    if (data == 'a') 
    {
      Serial.println(data);
      lcd.setCursor(0, 0);
      lcd.print("  !!Warning!!  ");
      delay(500);
      lcd.clear();
      
    } 
  
    else if (rfid.uid.uidByte[0] == 229 && rfid.uid.uidByte[1] == 114 && rfid.uid.uidByte[2] == 18 && rfid.uid.uidByte[3] == 173) 
    {
      data = NULL;
    }

  if (data == 'b') 
  {
    Serial.println(data);
    lcd.setCursor(0, 1);
    lcd.print("  Normal  ");
    delay(1000);
    lcd.clear();
  }
  

  // RFID 카드 아이디 알아내기
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    delay(500);
    return;
  }

  Serial.print("Card UID: ");

  for (byte i = 0; i < 4; i++) {
    Serial.print(rfid.uid.uidByte[i]);
    Serial.print(" ");
  }
  if (rfid.uid.uidByte[0] == 229 && rfid.uid.uidByte[1] == 114 && rfid.uid.uidByte[2] == 18 && rfid.uid.uidByte[3] == 173) 
  {
    if(data == 'a')
    {
      P_Serial.write('n');
      lcd.setCursor(0, 1);
      lcd.print("  Normal  ");
       delay(1000);
    }
    else if(data == 'n')
    {
      lcd.setCursor(0, 1);
      lcd.print("  maintenance!!  ");
      data = m;
    }
  }
  Serial.println();
  
}
