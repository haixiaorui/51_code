#include <STC89C5xRC.H>
#include "LCD1602.h"
#include "Delay.h"
#include "IR.h"

unsigned char num;
unsigned char address;
unsigned char command;

void main()
{
    LCD_Init();
	LCD_ShowString(1, 1, "ADDR  CMD  NUM");
	LCD_ShowString(2, 1, "00    00   000");
	IR_Init();
	
    while(1)
    {
        if(IR_GetDataFlag() || IR_GetRepeatFlag())
		{
			address = IR_GetAddress();
			command = IR_GetCommand();
			
			LCD_ShowHexNum(2, 1, address, 2);
			LCD_ShowHexNum(2, 7, command, 2);
			
			if(command == IR_VOL_MINUS)
			{
				num--;
			}
			if(command == IR_VOL_ADD)
			{
				num++;
			}
			LCD_ShowNum(2, 12, num, 3);
		}
    }
}
