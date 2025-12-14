#include <STC89C5xRC.H>
#include "Delay.h"
#include "Key.h"
#include "Nixie.h"
#include "Timer0.h"

sbit Motor = P1^0;

unsigned char counter, compare;
unsigned char KeyNum, speed;

void main()
{
    Timer0_Init();
	compare = 5;
    while(1)
    {
        KeyNum = Key();
		if(KeyNum == 1)
		{
			speed++;
			speed %= 4;
			if(speed == 0) compare = 0;
			if(speed == 1) compare = 50;
			if(speed == 2) compare = 75;
			if(speed == 3) compare = 100;
		}
		NixieDisp(1, speed);
    }
}

void Timer0_Routine()	interrupt 1
{
	TL0 = 0xA4;				//设置定时初始值
	TH0 = 0xFF;				//设置定时初始值
	counter++;
	counter %= 100;
	if(counter < compare) Motor = 1;
	else Motor = 0;
}