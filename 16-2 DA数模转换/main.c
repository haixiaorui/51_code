#include <STC89C5xRC.H>
#include "Delay.h"
#include "Key.h"
#include "Nixie.h"
#include "Timer0.h"

sbit DA = P2^1;

unsigned char counter, compare;
unsigned char i;

void main()
{
    Timer0_Init();
    while(1)
    {
        for(i = 0; i < 100; i++)
		{
			compare = i;
			Delayms(10);
		}
		for(i = 100; i > 0; i--)
		{
			compare = i;
			Delayms(10);
		}
    }
}

void Timer0_Routine()	interrupt 1
{
	TL0 = 0xA4;				//设置定时初始值
	TH0 = 0xFF;				//设置定时初始值
	counter++;
	counter %= 100;
	if(counter < compare) DA = 1;
	else DA = 0;
}