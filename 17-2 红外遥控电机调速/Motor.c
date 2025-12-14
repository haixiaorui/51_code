#include <STC89C5xRC.H>
#include "Timer1.h"

sbit Motor = P1^0;

unsigned char counter, compare;

void Motor_Init(void)
{
	Timer1_Init();
}

void Motor_SetSpeed(unsigned char speed)
{
	compare = speed;
}

void Timer1_Routine()	interrupt 3
{
	TL1 = 0xA4;				//设置定时初始值
	TH1 = 0xFF;				//设置定时初始值
	counter++;
	counter %= 100;
	if(counter < compare) Motor = 1;
	else Motor = 0;
}