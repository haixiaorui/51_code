#include <STC89C5xRC.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char KeyNum;

void main()
{
	LCD_Init();
	LCD_ShowString(1, 1, "MatrixKey:");
	while(1)
	{
		KeyNum = KeyDown();
		if(KeyNum) {
			LCD_ShowNum(2, 1, KeyNum, 2);
		}
	}
} 