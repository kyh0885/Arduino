#include <SoftwareSerial.h>
//여기는 RX
SoftwareSerial P_Serial(6,7);
char str[50];
char *sArr[4];

void setup() 
{
  Serial.begin(9600); //pc랑 통신
  P_Serial.begin(9600); //아두이노랑 통신
}

void loop() 
{
  int index = 0, i = 0;
  char *ptr = NULL;
  while(P_Serial.available())
  {
    str[index++] = P_Serial.read();
  }
  str[index] = '\0';
  ptr = strtok(str,"#"); //strtok은 문자를 쪼개는것 
  while(ptr!=NULL)
  {
    sArr[i++] = ptr;
    ptr = strtok(NULL," ");
  }
  int a = atoi(sArr[0]);
  int b = atoi(sArr[1]);

  Serial.println(a);
  Serial.println(b);
}
