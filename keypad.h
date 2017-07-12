/*
 * keypad.h
 *
 * Created: 5/5/2017 4:54:08 PM
 *  Author: OBED
 */ 

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>
#include <util/delay.h>


#ifndef KEYPAD_PORT
# define KEYPAD_PORT	PORTA
#endif

#ifndef KEYPAD_PIN
# define KEYPAD_PIN	PINA
#endif


unsigned char read_keypad(void);

unsigned char read_keypad(void)
{
	unsigned char keypad_input=0xff,keypad_output=0xff;
	KEYPAD_PORT=0xfe;
	_delay_us(2);
	keypad_input=KEYPAD_PIN & 0xf0;

	if(keypad_input==0xe0)
	keypad_output=0x01;
	else if(keypad_input==0xd0)
	keypad_output=0x02;
	else if(keypad_input==0xb0)
	keypad_output=0x03;
	else if(keypad_input==0x70)
	keypad_output=0x0c;
	else
	;

	KEYPAD_PORT=0xfd;
	_delay_us(2);
	keypad_input=KEYPAD_PIN & 0xf0;

	if(keypad_input==0xe0)
	keypad_output=0x04;
	else if(keypad_input==0xd0)
	keypad_output=0x05;
	else if(keypad_input==0xb0)
	keypad_output=0x06;
	else if(keypad_input==0x70)
	keypad_output=0x0d;
	else
	;

	KEYPAD_PORT=0xfb;
	_delay_us(2);
	keypad_input=KEYPAD_PIN & 0xf0;

	if(keypad_input==0xe0)
	keypad_output=0x07;
	else if(keypad_input==0xd0)
	keypad_output=0x08;
	else if(keypad_input==0xb0)
	keypad_output=0x09;
	else if(keypad_input==0x70)
	keypad_output=0x0e;
	else
	;
	
	KEYPAD_PORT=0xf7;
	_delay_us(2);
	keypad_input=KEYPAD_PIN & 0xf0;

	if(keypad_input==0xe0)
	keypad_output=0x0a;
	else if(keypad_input==0xd0)
	keypad_output=0x00;
	else if(keypad_input==0xb0)
	keypad_output=0x0b;
	else if(keypad_input==0x70)
	keypad_output=0x0f;
	else
	;
	return keypad_output;
}

// 			if(key !=0xff)
// 			{
// 				switch(key)
// 				{
// 					case 0:
// 					LCD_PrintString("D",0,0);
// 					break;
// 					case 1:
// 					LCD_PrintString("1",0,0);
// 					break;
// 					case 2:
// 					LCD_PrintString("A",0,0);
// 					break;
// 					case 3:
// 					LCD_PrintString("3",0,0);
// 					break;
// 					case 4:
// 					LCD_PrintString("4",0,0);
// 					break;
// 					case 5:
// 					LCD_PrintString("B",0,0);
// 					break;
// 					case 6:
// 					LCD_PrintString("6",0,0);
// 					break;
// 					case 7:
// 					LCD_PrintString("7",0,0);
// 					break;
// 					case 8:
// 					LCD_PrintString("C",0,0);
// 					break;
// 					case 9:
// 					LCD_PrintString("9",0,0);
// 					break;
// 					case 10:
// 					LCD_PrintString("*",0,0);
// 					break;
// 					case 11:
// 					LCD_PrintString("#",0,0);
// 					break;
// 					case 12:
// 					LCD_PrintString("2",0,0);
// 					break;
// 					case 13:
// 					LCD_PrintString("5",0,0);
// 					break;
// 					case 14:
// 					LCD_PrintString("8",0,0);
// 					break;
// 					case 15:
// 					LCD_PrintString("0",0,0);
// 					break;
// 				}
// 			}
// 			else
// 			{
// 				;				/*Null statement*/
//
// 			}
// 		//_delay_ms(500);
//}
#endif /* KEYPAD_H_ */