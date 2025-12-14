#include <STC89C5xRC.H>
#include "OneWire.h"

#define DS13B20_SKIP_ROM 			0xCC
#define DS13B20_CONVERT_T 			0x44
#define DS13B20_READ_SCRATCHPAD		0xBE

void DS18B20_ConvertT(void)
{
	OneWire_Init();
	OneWire_SendByte(DS13B20_SKIP_ROM);
	OneWire_SendByte(DS13B20_CONVERT_T);
}

float DS18B20_ReadT(void)
{
	unsigned char TLSB, TMSB;
	int temp;
	float T;
	OneWire_Init();
	OneWire_SendByte(DS13B20_SKIP_ROM);
	OneWire_SendByte(DS13B20_READ_SCRATCHPAD);
	TLSB = OneWire_ReceiveByte();
	TMSB = OneWire_ReceiveByte();
	temp = (TMSB << 8) | TLSB;
	T = temp / 16.0;
	return T;
}