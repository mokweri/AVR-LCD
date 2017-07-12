/*
 * LCD_Keypad.cpp
 *
 * Created: 4/24/2017 5:26:29 PM
 * Author : OBED
 */ 
#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "myLCD.c"
#include "keypad.h"


int main(void)
{
    LCDinit();
	LCDclr();
	 DDRA = 0x0f;  //Initialize Keypad Port
	 PORTA = 0xff;
	int checkpassword(char p[4]);
	
	unsigned char key;
	bool loged_in = false;
	
    while (1) 
    {
		
		char password[5];
				
		while (loged_in == false)
		{
			LCD_PrintString("Enter Password:",0,0);
				int i=0;			
				while(i<4)
				{
					key=read_keypad();
					if(key != 0xff)
					{
						password[i]=key+48;						
						i++;
						LCD_PrintString("*:",i,1);
					}
					else
					{
						;						/*Null statement*/
					}
					_delay_ms(200);			/*200ms delay as guard time between two consecutive pressing of key*/
				}
				i=0;
			password[4] = 0;
			
			if (checkpassword(password))
			{
				loged_in = true;
				LCDclr();
				LCD_PrintString("Log in success",0,0);
			} else{
				LCDclr();
				LCD_PrintString("Wrong password!",0,0);
				_delay_ms(2000);
				loged_in = false;
			}
			
		}		
			//itoa(key,s,10);
	  }
}

int checkpassword(char p[5])
{
	char mypass[]= "1234";
	bool correct;
	
	if (!(strcmp(p,mypass)))
	{
		correct = true;
	}else{
		correct = false;
	}
	return correct; //password correct
}