#include <STC89C5xRC.H>
#include "LCD1602.h"
#include "key.h"
#include "Delay.h"
#include "AT24C02.h"

unsigned char KeyNum;
unsigned int num;

void main()
{
    LCD_Init();
	LCD_ShowNum(1, 1, num, 5);
    while(1)
    {
        KeyNum = Key();
		if(KeyNum == 1)
		{
			num++;
			LCD_ShowNum(1, 1, num, 5);
		}
		if(KeyNum == 2)
		{
			num--;
			LCD_ShowNum(1, 1, num, 5);
		}
		if(KeyNum == 3)
		{
			AT24C02_WriteByte(0, num%256);
			Delayms(5);
			AT24C02_WriteByte(1, num/256);
			Delayms(5);
			LCD_ShowString(2, 1, "Write OK");
			Delayms(1000);
			LCD_ShowString(2, 1, "        ");
		}
		if(KeyNum == 4)
		{
			num = AT24C02_ReadByte(0);
			num |= AT24C02_ReadByte(1) << 8;
			LCD_ShowNum(1, 1, num, 5);
			LCD_ShowString(2, 1, "Read OK ");
			Delayms(1000);
			LCD_ShowString(2, 1, "        ");
		}
    }
}