#include <STC89C5xRC.H>
#include "OneWireDelay.h"

sbit OneWire_DQ = P3^7;

unsigned char OneWire_Init(void)
{
	unsigned char AckBit;
	OneWire_DQ = 1;
	OneWire_DQ = 0;
	Delay500us();
	OneWire_DQ = 1;
	Delay70us();
	AckBit = OneWire_DQ;
	Delay500us();
	return AckBit;
}

void OneWire_SendBit(unsigned char Bit)
{
	OneWire_DQ = 0;
	Delay10us();
	OneWire_DQ = Bit;
	Delay50us();
	OneWire_DQ = 1;
}

unsigned char OneWire_ReceiveBit(void)
{
	unsigned char i;
	unsigned char Bit;
	OneWire_DQ = 0;
	i = 2; while(--i);		// Delay5us
	OneWire_DQ = 1;
	i = 2; while(--i);		// Delay5us
	Bit = OneWire_DQ;
	Delay50us();
	return Bit;
}

void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		OneWire_SendBit(Byte & (0x01 << i));
	}
}

unsigned char OneWire_ReceiveByte(void)
{
	unsigned char i;
	unsigned char Byte = 0x00;
	for(i = 0; i < 8; i++)
	{
		if(OneWire_ReceiveBit())
		{
			Byte |= (0x01 << i);
		}
	}
	return Byte;
}