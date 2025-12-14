#include <STC89C5xRC.H>
#include <stdio.h>
#include "DS18B20.h"
#include "LCD1602.h"
#include "Delay.h"
#include "AT24C02.h"
#include "Timer0.h"
#include "key.h"

float T;
char text[10];
char Tlow, Thigh;
unsigned char KeyNum;

void main()
{
	DS18B20_ConvertT();
	Delayms(1000);
	Thigh = AT24C02_ReadByte(0);
	Tlow = AT24C02_ReadByte(1);
	if(Thigh > 125 || Tlow < -55 || Thigh <= Tlow)
	{
		Thigh = 30;
		Tlow = 10;
	}
	LCD_Init();
    LCD_ShowString(1, 1, "T:");
	LCD_ShowString(2, 1, "TH:");
	LCD_ShowString(2, 9, "TL:");
	LCD_ShowSignedNum(2, 4, Thigh, 3);
	LCD_ShowSignedNum(2, 12, Tlow, 3);
	Timer0_Init();
    while(1)
    {
		KeyNum = Key();
		/*温度读取及显示*/
        DS18B20_ConvertT();
		T = DS18B20_ReadT();
		sprintf(text, "%.2f", T);
		LCD_ShowString(1, 3, text);
		
		/*阈值判断及显示*/
		if(KeyNum)
		{
			if(KeyNum == 1) 
			{
				Thigh++;
				if(Thigh > 125) Thigh = 125;
			}
			if(KeyNum == 2) 
			{
				Thigh--;
				if(Thigh <= Tlow) Thigh++;
			}
			if(KeyNum == 3) 
			{
				Tlow++;
				if(Tlow >= Thigh) Tlow--;
			}
			if(KeyNum == 4) 
			{
				Tlow--;
				if(Tlow < -55) Tlow = -55;
			}
			LCD_ShowSignedNum(2, 4, Thigh, 3);
			LCD_ShowSignedNum(2, 12, Tlow, 3);
			AT24C02_WriteByte(0, Thigh);
			Delayms(5);
			AT24C02_WriteByte(1, Tlow);
			Delayms(5);
		}
		if(T > Thigh)
		{
			LCD_ShowString(1, 13, "OV:H");
		}
		else if(T < Tlow)
		{
			LCD_ShowString(1, 13, "OV:L");
		}
		else
		{
			LCD_ShowString(1, 13, "    ");
		}
    }
}

void Timer0_Routine()	interrupt 1
{
	static unsigned int T0count;
	TH0 = 64535 / 256;
	TL0 = 64535 % 256;
	T0count++;
	if(T0count >= 20)
	{
		T0count = 0;
		Key_Loop();
	}
}