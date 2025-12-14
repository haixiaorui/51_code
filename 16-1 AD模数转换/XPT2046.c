#include <STC89C5xRC.H>
#include "Delay.h"

sbit XPT2046_CS = P3^5;
sbit XPT2046_DCLK = P3^6;
sbit XPT2046_DIN = P3^4;
sbit XPT2046_DOUT = P3^7;

unsigned int XPT2046_ReadAD(unsigned char command)
{
	unsigned char i;
	unsigned int ADvalue;
	XPT2046_CS = 0;
	XPT2046_DCLK = 0;
	for(i = 0; i < 8; i++)
	{
		XPT2046_DIN = command & (0x80 >> i);
		XPT2046_DCLK = 1;
		Delayms(1);
		XPT2046_DCLK = 0;
	}
	for(i = 0; i < 16; i++)
	{
		XPT2046_DCLK = 1;
		Delayms(1);
		XPT2046_DCLK = 0;
		if(XPT2046_DOUT) ADvalue |= (0x8000 >> i);
	}
	if(command & 0x08) return ADvalue >> 8;
	else return ADvalue >> 4;
}