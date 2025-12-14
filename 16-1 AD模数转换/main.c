#include <STC89C5xRC.H>
#include "LCD1602.h"
#include "Delay.h"
#include "XPT2046.h"

unsigned int ADvalue;

void main()
{
    LCD_Init();
	LCD_ShowString(1, 1, "ADJ  NTC  RG");
    while(1)
    {
        ADvalue = XPT2046_ReadAD(XPT2046_XP_8);
		LCD_ShowNum(2, 1, ADvalue, 3);
		ADvalue = XPT2046_ReadAD(XPT2046_YP_8);
		LCD_ShowNum(2, 6, ADvalue, 3);
		ADvalue = XPT2046_ReadAD(XPT2046_VBAT_8);
		LCD_ShowNum(2, 11, ADvalue, 3);
		Delayms(10);
    }
}