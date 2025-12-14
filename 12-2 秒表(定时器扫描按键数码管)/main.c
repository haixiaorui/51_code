#include <STC89C5xRC.H>
#include "Timer0.h"
#include "Key.h"
#include "Nixie.h"
#include "AT24C02.h"
#include "Delay.h"

unsigned char KeyNum;
unsigned char min, sec, miniSec;
unsigned char runFlag;

void main()
{
    Timer0_Init();
    while(1)
    {
        KeyNum = Key();
		if(KeyNum == 1)
		{
			runFlag = !runFlag;
		}
		if(KeyNum == 2)
		{
			min = 0;
			sec = 0;
			miniSec = 0;
		}
		if(KeyNum == 3)
		{
			AT24C02_WriteByte(0, min);
			Delayms(5);
			AT24C02_WriteByte(1, sec);
			Delayms(5);
			AT24C02_WriteByte(2, miniSec);
		}
		if(KeyNum == 4)
		{
			min = AT24C02_ReadByte(0);
			sec = AT24C02_ReadByte(1);
			miniSec = AT24C02_ReadByte(2);
		}
		Nixie_SetBuf(1, min/10);
		Nixie_SetBuf(2, min%10);
		Nixie_SetBuf(3, 11);
		Nixie_SetBuf(4, sec/10);
		Nixie_SetBuf(5, sec%10);
		Nixie_SetBuf(6, 11);
		Nixie_SetBuf(7, miniSec/10);
		Nixie_SetBuf(8, miniSec%10);
    }
}

void Sec_Loop(void)
{
	if(runFlag)
	{
		miniSec++;
		if(miniSec >= 100)
		{
			miniSec = 0;
			sec++;
			if(sec >= 60)
			{
				sec = 0;
				min++;
				if(min >= 60)
				{
					min = 0;
				}
			}
		}
	}
	
}

void Timer0_Routine()	interrupt 1
{
	static unsigned int T0count1, T0count2, T0count3;
	TH0 = 64535 / 256;
	TL0 = 64535 % 256;
	T0count1++;
	if(T0count1 >= 20)
	{
		T0count1 = 0;
		Key_Loop();
	}
	T0count2++;
	if(T0count2 >= 2)
	{
		T0count2 = 0;
		Nixie_Loop();
	}
	T0count3++;
	if(T0count3 >= 10)
	{
		T0count3 = 0;
		Sec_Loop();
	}
}