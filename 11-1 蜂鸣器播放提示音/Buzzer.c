#include <STC89C5xRC.H>
#include <INTRINS.H>
#include "Delay.h"

// 蜂鸣器端口
sbit buzzer = P2^5;

/**
   * @brief  蜂鸣器私有延时函数，延时500us
   * @param  无
   * @retval 无
   */
void Buzzer_Delay500us(void)	//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 227;
	while (--i);
}

/**
   * @brief  蜂鸣器发声
   * @param  ms：发声的时长
   * @retval 无
   */
void BuzzerTime(unsigned int ms)
{
	unsigned int i;
	for(i = 0; i < ms*2; i++)
	{
		buzzer = !buzzer;
		Buzzer_Delay500us();
	}
}