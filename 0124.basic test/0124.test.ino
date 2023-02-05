int LED = 6;

void setup() 
{
  pinMode(LED, OUTPUT); //핀모드 LED 출력으로 설정
}

void loop() 
{
  digitalWrite(LED,HIGH); //LED를 켜라
  delay(1000);
  digitalWrite(LED,LOW);
  delay(1000);
}