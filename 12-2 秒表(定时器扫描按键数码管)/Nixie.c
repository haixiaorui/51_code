#include <STC89C5xRC.H>
#include "Delay.h"

unsigned char Nixie_Buf[9] = {0, 10, 10, 10, 10, 10, 10, 10, 10};

unsigned char NixieTable[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x00, 0x40};

void Nixie_SetBuf(unsigned char Location, unsigned char Number)
{
	Nixie_Buf[Location] = Number;
}

void Nixie_Scan(unsigned char Location, unsigned char Number)
{
	P0 = 0x00;
	switch(Location)
	{
		case 1: P24 = 1; P23 = 1; P22 = 1; break;
		case 2: P24 = 1; P23 = 1; P22 = 0; break;
		case 3: P24 = 1; P23 = 0; P22 = 1; break;
		case 4: P24 = 1; P23 = 0; P22 = 0; break;
		case 5: P24 = 0; P23 = 1; P22 = 1; break;
		case 6: P24 = 0; P23 = 1; P22 = 0; break;
		case 7: P24 = 0; P23 = 0; P22 = 1; break;
		case 8: P24 = 0; P23 = 0; P22 = 0; break;
	}
	P0 = NixieTable[Number];
}

void Nixie_Loop(void)
{
	static signed char i = 1;
	Nixie_Scan(i, Nixie_Buf[i]);
	i++;
	if(i > 8) i = 1;
}