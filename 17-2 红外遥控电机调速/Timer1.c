#include <STC89C5xRC.H>

/**
   * @brief 定时器0初始化，100us@11.0592MHz
   * @param 无
   * @retval 无
   */
void Timer1_Init(void)
{
	TMOD &= 0x0F;			//设置定时器模式
	TMOD |= 0x10;			//设置定时器模式
	TL1 = 0x9C;				//设置定时初始值
	TH1 = 0xFF;				//设置定时初始值
	TF1 = 0;				//清除TF0标志
	TR1 = 1;				//定时器0开始计时
	ET1 = 1;
	EA = 1;
	PT1 = 0;
}

/* 定时器中断函数模版
void Timer1_Routine()	interrupt 3
{
	static unsigned int T1count;
	TL1 = 0xA4;				//设置定时初始值
	TH1 = 0xFF;				//设置定时初始值
	T1count++;
	if(T1count >= 1000)
	{
		T1count = 0;
		
	}
}
*/