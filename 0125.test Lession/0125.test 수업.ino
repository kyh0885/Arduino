#include <IRremote.h>
#include <MsTimer2.h>
#include <Servo.h>

int LED = 3;
int servoPin = 9;
Servo servo;
int angle = 0;
int trig = 6;
int echo = 5;
int buz = 10;
int Switch = 2;
int buttonState = 0;
int RECV_PIN =2;
IRrecv irrecv(RECV_PIN);
decode_results results;
int remote;


volatile byte state = HIGH;
unsigned long pre_time = 0;
unsigned long cur_time = 0;

void isr()
{
    
    /*digitalWrite(LED, state);
    state = !state;
    Serial.println(state);*/
    static int count = 0;
    Serial.println(count++);
    /*cur_time = millis(); // cur_time은 계속 카운트 되고있음
    if(cur_time - pre_time >= 100) // 연속으로 누르는것을 방지하기 위함
    {                              
      Serial.println(count++);
      pre_time = cur_time; 
    }*/
  
}
void setup() 
{
  pinMode(LED, OUTPUT);  //핀모드 LED 출력으로 설정
  pinMode(A5, INPUT);
  pinMode(A4, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buz, OUTPUT);
  //pinMode(Switch, INPUT);
 // attachInterrupt(0, isr, RISING);
  MsTimer2::set(1000,isr); 
  MsTimer2::start();
  irrecv.enableIRIn();
  Serial.begin(9600);

  servo.attach(servoPin);
}

void loop() 
{
  int data = analogRead(A5);
  delay(100);

  /*Serial.print("pre : ");
  Serial.print(data);
  Serial.print("\tafter :");
  data = map(data, 0, 1023, 0, 255);
  Serial.println(data);

  analogWrite(LED,data);
  delay(100);

  
  for(angle = 0; angle < 180; angle++)
  {
    servo.write(angle);
    Serial.println(angle);
    delay(50);
  }
  if (Serial.available() > 0)
  {
    char data = Serial.read();
    if (data == 'a') 
    {
      digitalWrite(LED, HIGH);

      for (angle = 0; angle < 180; angle++) {
        servo.write(angle);
        Serial.println(angle);
        delay(50);
      }
    } 
    else if (data == 'b') 
    {
      digitalWrite(LED, HIGH);
      delay(5000);
      digitalWrite(LED, LOW);
      delay(5000);
    }
  }
  int light = analogRead(A4);
  delay(100);
  Serial.println(light);
  if(light<200)
  {
    digitalWrite(LED, HIGH);
    for (angle = 0; angle < 180; angle++) 
      {
        servo.write(angle);
        Serial.println(light);
        delay(50);
      }
  }
  else if(light>200)
  {
    digitalWrite(LED, LOW);
  }
  float duration, distance;
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = ((float)(340*duration) / 10000)/2;
  Serial.print("Duration : ");
  Serial.print(duration);
  Serial.print("\nDistance : ");
  Serial.print(distance);
  Serial.println("cm\n");
  delay(100);

  if(distance<20)
  {
  digitalWrite(buz, HIGH);
  delay(10 * distance);
  digitalWrite(buz, LOW);
  delay(10 * distance);
  }
  buttonState = digitalRead(Switch);
  if(buttonState == HIGH)
  {
    Serial.println("1");
  }
  else
  {
    Serial.println("0");
  }
  if(irrecv.decode(&results))
  {
    remote = results.value;
    Serial.println(remote);
    irrecv.resume();
    if(remote == 6375)
    {
      digitalWrite(LED, HIGH);
    }
    else
    {
      digitalWrite(LED, LOW);
    }
  }*/
}