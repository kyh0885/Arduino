#include <Wire.h>
#include <LiquidCrystal_I2C.h>
char data;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
	lcd.init();
	lcd.backlight();
  Serial.begin(9600);
}

void loop() 
{ 
  
  if(Serial.available())
  {
    data = Serial.read();
  }
	if (data == 'a') 
  {
		Serial.println(data);
    lcd.setCursor(0,0);		    		
		lcd.print("  BYE  ");     
	}
	else if (data == 'b') 
  {
		Serial.println(data);
    lcd.setCursor(0,1);		    		
		lcd.print("  Hello World!!  ");   	
	}
	delay(1000);
	lcd.clear();
}