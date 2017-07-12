/*
 * myLCD.c
 *
 * Created: 1/25/2017 11:41:53 AM
 *  Author: Obed
 */ 
#define F_CPU 1000000UL
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>
#include "myLCD.h"

void LCDinit(void)//Initializes LCD
{
	#ifdef LCD_4bit
	//4 bit part
	_delay_ms(15);
	LDP=0x00;
	LCP=0x00;
	LDDR|=1<<LCD_D7|1<<LCD_D6|1<<LCD_D5|1<<LCD_D4;
	LCDR|=1<<LCD_E|1<<LCD_RW|1<<LCD_RS;
	//---------one------
	LDP=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4; //4 bit mode
	LCP|=1<<LCD_E|0<<LCD_RW|0<<LCD_RS;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	//-----------two-----------
	LDP=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4; //4 bit mode
	LCP|=1<<LCD_E|0<<LCD_RW|0<<LCD_RS;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	//-------three-------------
	LDP=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|0<<LCD_D4; //4 bit mode
	LCP|=1<<LCD_E|0<<LCD_RW|0<<LCD_RS;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	//--------4 bit--dual line---------------
	LCDsendCommand(0b00101000);
	//-----increment address, invisible cursor shift------
	LCDsendCommand(0b00001100);
	

	#else	//8 bit part
	_delay_ms(15);
	LDP=0x00;
	LCP=0x00;
	LDDR|=1<<LCD_D7|1<<LCD_D6|1<<LCD_D5|1<<LCD_D4|1<<LCD_D3|1<<LCD_D2|1<<LCD_D1|1<<LCD_D0;
	LCDR|=1<<LCD_E|1<<LCD_RW|1<<LCD_RS;
	//---------one------
	LDP=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4|0<<LCD_D3|0<<LCD_D2|0<<LCD_D1|0<<LCD_D0; //8 it mode
	LCP|=1<<LCD_E|0<<LCD_RW|0<<LCD_RS;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	//-----------two-----------
	LDP=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4|0<<LCD_D3|0<<LCD_D2|0<<LCD_D1|0<<LCD_D0; //8 it mode
	LCP|=1<<LCD_E|0<<LCD_RW|0<<LCD_RS;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	//-------three-------------
	LDP=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4|0<<LCD_D3|0<<LCD_D2|0<<LCD_D1|0<<LCD_D0; //8 it mode
	LCP|=1<<LCD_E|0<<LCD_RW|0<<LCD_RS;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	//--------8 bit dual line----------
	LDP=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4|1<<LCD_D3|0<<LCD_D2|0<<LCD_D1|0<<LCD_D0; //8 it mode
	LCP|=1<<LCD_E|0<<LCD_RW|0<<LCD_RS;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	//-----increment address, invisible cursor shift------
	LDP=0<<LCD_D7|0<<LCD_D6|0<<LCD_D5|0<<LCD_D4|1<<LCD_D3|1<<LCD_D2|0<<LCD_D1|0<<LCD_D0; //8 it mode
	LCP|=1<<LCD_E|0<<LCD_RW|0<<LCD_RS;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(5);
	#endif
}

void LCDsendChar(uint8_t ch)		//Sends Char to LCD
{

	#ifdef LCD_4bit
	//4 bit part
	LDP=(ch&0b11110000);
	LCP|=1<<LCD_RS;
	LCP|=1<<LCD_E;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	LCP&=~(1<<LCD_RS);
	_delay_ms(1);
	LDP=((ch&0b00001111)<<4);
	LCP|=1<<LCD_RS;
	LCP|=1<<LCD_E;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	LCP&=~(1<<LCD_RS);
	_delay_ms(1);
	#else
	//8 bit part
	LDP=ch;
	LCP|=1<<LCD_RS;
	LCP|=1<<LCD_E;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	LCP&=~(1<<LCD_RS);
	_delay_ms(1);
	#endif
}

void LCDsendCommand(uint8_t cmd)	//Sends Command to LCD
{
	#ifdef LCD_4bit
	//4 bit part
	LDP=(cmd&0b11110000);
	LCP|=1<<LCD_E;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	LDP=((cmd&0b00001111)<<4);
	LCP|=1<<LCD_E;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	#else
	//8 bit part
	LDP=cmd;
	LCP|=1<<LCD_E;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	#endif
}


void LCDclr(void)				//Clears LCD
{
	LCDsendCommand(1<<LCD_CLR);
}
void LCDhome(void)			//LCD cursor home
{
	LCDsendCommand(1<<LCD_HOME);
}
void LCDstring(uint8_t* data, uint8_t nBytes)	//Outputs string to LCD
{
	register uint8_t i;

	// check to make sure we have a good pointer
	if (!data) return;

	// print data
	for(i=0; i<nBytes; i++)
	{
		LCDsendChar(data[i]);
	}
}
void LCDGotoXY(uint8_t x, uint8_t y)	//Cursor to X Y position
{
	register uint8_t DDRAMAddr;
	// remap lines into proper order
	switch(y)
	{
		case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR+x; break;
		case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR+x; break;
		case 2: DDRAMAddr = LCD_LINE2_DDRAMADDR+x; break;
		case 3: DDRAMAddr = LCD_LINE3_DDRAMADDR+x; break;
		default: DDRAMAddr = LCD_LINE0_DDRAMADDR+x;
	}
	// set data address
	LCDsendCommand(1<<LCD_DDRAM | DDRAMAddr);
	
}
//Copies string from flash memory to LCD at x y position
//const uint8_t welcomeln1[] PROGMEM="AVR LCD DEMO\0";
//CopyStringtoLCD(welcomeln1, 3, 1);
void CopyStringtoLCD(const uint8_t *FlashLoc, uint8_t x, uint8_t y)
{
	uint8_t i;
	LCDGotoXY(x,y);
	for(i=0;(uint8_t)pgm_read_byte(&FlashLoc[i]);i++)
	{
		LCDsendChar((uint8_t)pgm_read_byte(&FlashLoc[i]));
		
	}
	// Wrap to the next line
	LCDsendCommand(1<<LCD_DDRAM | LCD_LINE1_DDRAMADDR);
	for(i=16;(uint8_t)pgm_read_byte(&FlashLoc[i]);i++)
	{
		LCDsendChar((uint8_t)pgm_read_byte(&FlashLoc[i]));
		
	}
}

void LCD_PrintString(const char *s,uint8_t x,uint8_t y)
/* print string on lcd) */
{
	uint8_t i;
	LCDGotoXY(x,y);
	register char c;
    uint8_t n;
	n=strlen(s);
	if (n<9)
	{
		for(i=0;i<n;i++)
		{
			c=*s++;
			LCDsendChar(c);
		}
	} 
	else
	{
		for(i=0;i<n;i++)
		{
			c=*s++;
			LCDsendChar(c);
		}
		// Wrap to the next line
		LCDsendCommand(1<<LCD_DDRAM | LCD_LINE1_DDRAMADDR);
		for(i=16;i<n;i++)
		{
			c = *s++;
			LCDsendChar(c);
		}
	}

}/* PrintString */

void LCDshiftLeft(uint8_t n)	//Scrol n of characters Right
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDsendCommand(0x1E);
	}
}
void LCDshiftRight(uint8_t n)	//Scrol n of characters Left
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDsendCommand(0x18);
	}
}
void LCDcursorOn(void) //displays LCD cursor
{
	LCDsendCommand(0x0E);
}
void LCDcursorOnBlink(void)	//displays LCD blinking cursor
{
	LCDsendCommand(0x0F);
}
void LCDcursorOFF(void)	//turns OFF cursor
{
	LCDsendCommand(0x0C);
}
void LCDblank(void)		//blanks LCD
{
	LCDsendCommand(0x08);
}
void LCDvisible(void)		//Shows LCD
{
	LCDsendCommand(0x0C);
}
void LCDcursorLeft(uint8_t n)	//Moves cursor by n poisitions left
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDsendCommand(0x10);
	}
}
void LCDcursorRight(uint8_t n)	//Moves cursor by n poisitions left
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDsendCommand(0x14);
	}
}
