#include <REGX52.H>

/**
* @brief	定时器0初始化，晶振频率为11.0592MHz
  * @param	
  * @retval	
  */

void Timer0_Init(){
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TH0 = 0xDC;
	TL0 = 0x00; //初始10ms溢出
	TF0 = 0;
	TR0 = 1;
	ET0 = 1;	//允许中断
	EA = 1; 	//允许总中断
	PT0 = 0;	//低优先级
}
/* 定时器中断函数模板
void Timer0_Routine() interrupt 1{
	static unsigned int T0Count;
	TH0 = 0xDC;
	TL0 = 0x00;
	T0Count++;
	if(T0Count >= 100){
		T0Count = 0;

	}
}
*/
