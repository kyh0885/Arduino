#include <SoftwareSerial.h>
//여기는 TX
SoftwareSerial P_Serial(6,7);

void setup() 
{
  //Serial.begin(9600); //0,1
  P_Serial.begin(9600); //6,7
}

void loop() 
{
  int i = 50, j = 20;
  String sensing1 = (String)i;
  String sensing2 = (String)j;
  String str = (String)sensing1+ "#" + (String)sensing2;
 // Serial.println(str);
  P_Serial.println(str);//이게 실제로 보내게 될 데이터
  delay(100);
}
