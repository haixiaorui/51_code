#include <STC89C5xRC.H>
#include "Delay.h"

/**
   * @brief 矩阵键盘读取按键键码
   * @param	无
   * @retval KeyNumber 按下按键的键码值
   如果按键按下不放，程序会停留在此函数，松手的一瞬间，返回按键键码，没有按键按下时，返回0
   */
unsigned char MatrixKey()
{
	unsigned char KeyNumber = 0;
	
	P1 = 0xff;
	P17 = 0;
	if(P13 == 0) { Delayms(20); while(P13 == 0); Delayms(20); KeyNumber = 1; }
	if(P12 == 0) { Delayms(20); while(P12 == 0); Delayms(20); KeyNumber = 2; }
	if(P11 == 0) { Delayms(20); while(P11 == 0); Delayms(20); KeyNumber = 3; }
	if(P10 == 0) { Delayms(20); while(P10 == 0); Delayms(20); KeyNumber = 4; }
	
	P1 = 0xff;
	P16 = 0;
	if(P13 == 0) { Delayms(20); while(P13 == 0); Delayms(20); KeyNumber = 5; }
	if(P12 == 0) { Delayms(20); while(P12 == 0); Delayms(20); KeyNumber = 6; }
	if(P11 == 0) { Delayms(20); while(P11 == 0); Delayms(20); KeyNumber = 7; }
	if(P10 == 0) { Delayms(20); while(P10 == 0); Delayms(20); KeyNumber = 8; }
	
	P1 = 0xff;
	P15 = 0;
	if(P13 == 0) { Delayms(20); while(P13 == 0); Delayms(20); KeyNumber = 9; }
	if(P12 == 0) { Delayms(20); while(P12 == 0); Delayms(20); KeyNumber = 10; }
	if(P11 == 0) { Delayms(20); while(P11 == 0); Delayms(20); KeyNumber = 11; }
	if(P10 == 0) { Delayms(20); while(P10 == 0); Delayms(20); KeyNumber = 12; }
	
	P1 = 0xff;
	P14 = 0;
	if(P13 == 0) { Delayms(20); while(P13 == 0); Delayms(20); KeyNumber = 13; }
	if(P12 == 0) { Delayms(20); while(P12 == 0); Delayms(20); KeyNumber = 14; }
	if(P11 == 0) { Delayms(20); while(P11 == 0); Delayms(20); KeyNumber = 15; }
	if(P10 == 0) { Delayms(20); while(P10 == 0); Delayms(20); KeyNumber = 16; }
	
	return KeyNumber;
}

unsigned char KeyDown()
{
	char a = 0;
	unsigned char KeyValue = 0;
	P1 = 0x0f;
	if(P1 != 0x0f)	// 读取按键是否按下
	{
		Delayms(10);
		if(P1 != 0x0f)
		{
			// 测试列
			P1 = 0x0f;
			switch(P1)
			{
				case(0x07): KeyValue = 1; break;
				case(0x0b): KeyValue = 2; break;
				case(0x0d): KeyValue = 3; break;
				case(0x0e): KeyValue = 4; break;
			}
			// 测试行
			P1 = 0xf0;
			switch(P1)
			{
				case(0x70): KeyValue = KeyValue; break;
				case(0xB0): KeyValue += 4; break;
				case(0xD0): KeyValue += 8; break;
				case(0xe0): KeyValue += 12; break;
			}
			while((a < 50) && (P1 != 0xf0))	// 检测按键松手检测
			{
				Delayms(10);
				a++;
			}
		}
	}
	return KeyValue;
}