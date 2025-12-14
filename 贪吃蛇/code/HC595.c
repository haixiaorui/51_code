#include <REGX52.H>
#include "Delay.H"
#include "INTRINS.H"
sbit SER=P3^4;
sbit SCK=P3^6;
sbit RCK=P3^5;
void _74HC595(unsigned char Byte)
{	
	unsigned char i;
	SCK=0;
	RCK=0;
	for(i=0;i<8;i++)
	{
		SER=Byte&(0x80>>i);
		SCK=1;
		_nop_();
		_nop_();
		SCK=0;
	}
	RCK=1;
	_nop_();
	_nop_();
	RCK=0;
}
void MatrixLed(unsigned char Column,Date)//Column是行，Date是列。
{
	_74HC595(Date);
	P0=(Column);
	Delay(1);
	P0=0xff;
}
