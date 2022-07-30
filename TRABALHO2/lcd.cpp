#include "lcd.hpp"  
#include "digital.h"    
#include "delay.hpp"

void lcd_dado (uint8_t d)
{
	digitalWrite(RS,HIGH);
	digitalWrite(D0, d & 1);
	digitalWrite(D1, (d>>1) & 1);
	digitalWrite(D2, (d>>2) & 1);
	digitalWrite(D3, (d>>3) & 1);
	digitalWrite(D4, (d>>4) & 1);
	digitalWrite(D5, (d>>5) & 1);
	digitalWrite(D6, (d>>6) & 1);
	digitalWrite(D7, (d>>7) & 1);
	digitalWrite(E, HIGH);
	delay_ms(4);
	digitalWrite(E, LOW);
	delay_ms(10);
	
}
void lcd_comando (uint8_t d)
{
	digitalWrite(RS,LOW);
	digitalWrite(D0, d & 1);
	digitalWrite(D1, (d>>1) & 1);
	digitalWrite(D2, (d>>2) & 1);
	digitalWrite(D3, (d>>3) & 1);
	digitalWrite(D4, (d>>4) & 1);
	digitalWrite(D5, (d>>5) & 1);
	digitalWrite(D6, (d>>6) & 1);
	digitalWrite(D7, (d>>7) & 1);
	digitalWrite(E, HIGH);
	delay_ms(40);
	digitalWrite(E, LOW);
	
	
}
void lcd_init (void)
{
    delay_ms(500);
    pinMode(D0,OUTPUT);
    pinMode(D1,OUTPUT);
    pinMode(D2,OUTPUT);
    pinMode(D3,OUTPUT);
    pinMode(D4,OUTPUT);
    pinMode(D5,OUTPUT);
    pinMode(D6,OUTPUT);
    pinMode(D7,OUTPUT);
    pinMode(RS,OUTPUT);
    pinMode(E,OUTPUT);

    digitalWrite(E,  LOW);
        delay_ms(40);
    
    lcd_comando (0x38);
    lcd_comando (0x01);
    lcd_comando (0x0F);  	
}

void lcd_msg(char *s)
{
	int x=0;
	while (s[x]!=0)
	{
		lcd_dado(s[x]);
		x++;
	}
}
