#include <STC89C5xRC.H>
#include "LCD1602.h"
#include "Delay.h"

int res = 0;

void main()
{
	LCD_Init();
	while(1)
	{
		res++;
		Delayms(1000);
		LCD_ShowNum(1, 1, res, 3);
	}
}