#include <STC89C5xRC.H>
#include "LCD1602.h"

void main()
{
    LCD_Init();
	LCD_ShowChar(1, 1, 0xB1);
	LCD_ShowChar(1, 2, 0xB2);
	LCD_ShowChar(1, 3, 0xBC);
	LCD_ShowChar(1, 4, 0xC3);
	LCD_ShowChar(1, 5, 0xD9);
    while(1)
    {
        
    }
}