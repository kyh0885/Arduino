#include <MsTimer2.h>
#include <SoftwareSerial.h>     //SPI 통신
#include <MFRC522.h>            // RFID
#include <SPI.h>                // RFID
#include <LiquidCrystal_I2C.h>  //LCD
#include <Wire.h>               //LCD

#define SS_PIN 10  //RFID
#define RST_PIN 9

SoftwareSerial P_Serial(4, 5);

char data;                           //LCD 문자
LiquidCrystal_I2C lcd(0x27, 16, 2);  //LCD 문자
int LED = 6; 

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

byte nuidPICC[4];  // RFID ID을 알아내기위한 배열 선언

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  P_Serial.begin(9600);

  pinMode(LED, OUTPUT);

  MsTimer2::set(30000,isr); //30초에 한번씩 Interrupt 시행
  MsTimer2::start();

  SPI.begin();      // Init SPI bus
  rfid.PCD_Init();  // Init MFRC522
}

void isr()
{ 
    digitalWrite(LED, 1);
    interrupts(); // Interrupt를 재구동
    lcd.clear(); // LCD 초기화
    lcd.setCursor(0, 1);
    lcd.print("  NEED CHECK!!  ");
    delay(3000);
    digitalWrite(LED, 0);

    Serial.println("INTERRUPT");    
}

void loop() {
 
  if (P_Serial.available())  //만약 읽을 데이터가 있을 시
  {
    data = P_Serial.read();
    Serial.print("data in : ");
    Serial.println(data);
  }
  if (rfid.uid.uidByte[0] == 229 && rfid.uid.uidByte[1] == 114 && rfid.uid.uidByte[2] == 18 && rfid.uid.uidByte[3] == 173) 
  {   
    if (data == 'n') {data = 'm';Serial.println("data n -> m ");}
    else if (data == 'w') {data = 'n';Serial.println("data w -> n ");}
    else if (data == 'm') {data = 'n';Serial.println("data m -> n ");}

    for (int i = 0; i < 4; i++) rfid.uid.uidByte[i] = NULL; // RFID 의 ID 를 초기화
  } 
    
  if (data == 'n') {
    Serial.print("data out : ");
    Serial.println(data);
    P_Serial.write('n');
    lcd.setCursor(0, 1);
    lcd.print("  Normal  ");
    delay(1000);
    lcd.clear();
  }
  if (data == 'w') {
    Serial.print("data out : ");
    Serial.println(data);
    P_Serial.write('w');
    lcd.setCursor(0, 1);
    lcd.print("  !!Warning!!  ");
    delay(1000);
    lcd.clear();
  }
  if (data == 'm') {
    Serial.print("data out : ");
    Serial.println(data);
    P_Serial.write('m');
    lcd.setCursor(0, 1);
    lcd.print("  maintenance!!  ");
    delay(1000);
    lcd.clear();
  }

  // RFID 카드 아이디 값 구함
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    delay(500);
    return;
  }
  Serial.print("Card UID: ");
  for (byte i = 0; i < 4; i++) {
    Serial.print(rfid.uid.uidByte[i]);
    Serial.print(" ");
  }
  Serial.println();
}