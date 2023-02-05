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
int Switch = 2; 
int LED = 6;
int count = 0;

unsigned long pre_time = 0;
unsigned long cur_time = 0;

byte state = 1;  // timer interrupt

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

byte nuidPICC[4];  // RFID ID을 알아내기위한 배열 선언

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  P_Serial.begin(9600);

  pinMode(Switch, INPUT);
  pinMode(LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(Switch), isr, FALLING);

  SPI.begin();      // Init SPI bus
  rfid.PCD_Init();  // Init MFRC522
}

void isr()
{ 
  cur_time = millis(); // cur_time은 계속 카운트 되고있음
    if(cur_time - pre_time >= 100) // 연속으로 누르는것을 방지하기 위함
    { 
      digitalWrite(LED, 1);
      while(count!=2000){
      delayMicroseconds(1000);
      count++;}
      count=0; 
      
      digitalWrite(LED, 0);
      Serial.println("INTERRUPT");    
      pre_time = cur_time;                       
    }
}

void loop() {
 
  //여기부터  LCD 제어/ 출력 관련
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

    for (int i = 0; i < 4; i++) rfid.uid.uidByte[i] = NULL;
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
  Serial.println();
}