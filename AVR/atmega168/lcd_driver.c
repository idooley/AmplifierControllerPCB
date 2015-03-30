//*****************************************************************************
//
// File Name	: 'main.c'
// Title		: LCD demo
// Author		: Scienceprog.com - Copyright (C) 2007
// Created		: 2007-03-29
// Revised		: 2011-12-13
// Version		: 1.0
// Target MCU	: Atmel AVR series
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lcd_lib.h"

//Strings stored in AVR Flash memory
const uint8_t LCDwelcomeln1[] PROGMEM="AVR LCD DEMO";
const uint8_t LCDprogress[] PROGMEM="Loading...";
const uint8_t LCDanimation[] PROGMEM=" LCD animation";

// additional custom LCD characters
const uint8_t backslash[8] PROGMEM= 
{
0b00000000,//back slash
0b00010000,
0b00001000,
0b00000100,
0b00000010,
0b00000001,
0b00000000,
0b00000000
};

//delay 1s
void delay1s(void)
{
	uint8_t i;
	for(i=0;i<100;i++)
	{
		_delay_ms(10);
	}
}
//demonstration of progress bar
void progress(void)
{
	LCDclr();
	CopyStringtoLCD(LCDwelcomeln1, 3, 0);	
	delay1s();
	LCDclr();
	CopyStringtoLCD(LCDprogress, 3, 0);
	for(uint8_t i=0;i<255;i++)
		{
			_delay_ms(10);
			LCDGotoXY(0, 1);
			LCDprogressBar(i, 255, 16);
		}
}
//demonstration of animation
void demoanimation(void)
{
	LCDclr();
	LCDdefinechar(backslash,0);
	CopyStringtoLCD(LCDanimation, 0, 0);
	for(uint8_t i=0;i<3;i++)
		{
			LCDGotoXY(8, 1);
			LCDsendChar(0);
			delay1s();
			LCDGotoXY(8, 1);
			LCDsendChar('-');
			delay1s();
			LCDGotoXY(8, 1);
			LCDsendChar('/');
			delay1s();
			LCDGotoXY(8, 1);
			LCDsendChar('|');
			delay1s();
			LCDGotoXY(8, 1);
			LCDsendChar(8);//backslash
			delay1s();
			LCDGotoXY(8, 1);
			LCDsendChar('-');
			delay1s();
			LCDGotoXY(8, 1);
			LCDsendChar('/');
			delay1s();
			LCDGotoXY(8, 1);
			LCDsendChar('|');
			delay1s();
		}	
}

int main(void)
{
	LCDinit();//init LCD bit, dual line, cursor right
	LCDclr();//clears LCD
	while(1)//loop demos
	{
		progress();
		delay1s();
		demoanimation();
	}
	return 0;
}
