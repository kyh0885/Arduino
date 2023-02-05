char data;
int LED = 13;

void setup() 
{
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
}

void loop() 
{
  if(Serial.available())
  {
    data = Serial.read();
  }
  if(data == 'a')
  {
    digitalWrite(LED, HIGH);
  }
  else if(data == 'b')
  {
    digitalWrite(LED, LOW);
  }

  Serial.write('c');
  delay(1000);
  Serial.write('d');
  delay(1000);
  
}