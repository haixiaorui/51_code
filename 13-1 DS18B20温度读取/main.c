#include <STC89C5xRC.H>
#include <stdio.h>
#include "LCD1602.h"
#include "Delay.h"
#include "DS18B20.h"

float T;
char text[10];

void main()
{
	DS18B20_ConvertT();
	Delayms(1000);
    LCD_Init();
	LCD_ShowString(1, 1, "Temperature:");
    while(1)
    {
        DS18B20_ConvertT();
		T = DS18B20_ReadT();
		sprintf(text, "%.4f", T);
		LCD_ShowString(2, 1, text);
    }
}