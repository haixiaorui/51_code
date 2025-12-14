#include <REGX52.H>
void Timer0_Init(void)
{
	TMOD &= 0xF0;		
	TMOD |= 0x01;		
	TL0 = 0xCD;		//设置定时初始值
	TH0 = 0xD4;		//设置定时初始值	
	TF0 = 0;		
	TR0 = 1;		
	ET0=1;
	EA=1;
	PT0=0;
}
