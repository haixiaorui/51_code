#include <STC89C5xRC.H>
#include <INTRINS.H>
#include <stdio.h>

sbit LCD_RS = P2^6; 
sbit LCD_RW = P2^5;
sbit LCD_E = P2^7;
#define LCD_DataPort P0

void LCD_Delay(void)	//@11.0592MHz 1ms
{
	unsigned char data i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void LCD_WriteCommand(unsigned char command)
{
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_DataPort = command;
	LCD_E = 1;
	LCD_Delay();
	LCD_E = 0;
	LCD_Delay();
}

void LCD_WriteData(unsigned char Data)
{
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_DataPort = Data;
	LCD_E = 1;
	LCD_Delay();
	LCD_E = 0;
	LCD_Delay();
}

void LCD_Init(void)
{
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x0C);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x01);
}

void LCD_SetCursor(unsigned char line, unsigned char column)
{
	if(line == 1)
	{
		LCD_WriteCommand(0x80 | (column - 1));
	}
	else
	{
		LCD_WriteCommand(0x80 | (column - 1) + 0x40);
	}
}

void LCD_ShowChar(unsigned char line, unsigned char column, unsigned char Char)
{
	LCD_SetCursor(line, column);
	LCD_WriteData(Char);
}

void LCD_ShowString(unsigned char line, unsigned char column, unsigned char* String)
{
	unsigned char i;
	LCD_SetCursor(line, column);
	for(i = 0; String[i] != '\0'; i++)
	{
		LCD_WriteData(String[i]);
	}
}

void LCD_ShowNum(unsigned char line, unsigned char column, unsigned int number)
{
	unsigned char text[5];
	LCD_SetCursor(line, column);
	sprintf(text, "%u", number);
	LCD_ShowString(line, column, text);
}

void LCD_ShowSignedNum(unsigned char line, unsigned char column, int number)
{
	unsigned char text[6];
	LCD_SetCursor(line, column);
	sprintf(text, "%d", number);
	LCD_ShowString(line, column, text);
}

void LCD_ShowHexNum(unsigned char line, unsigned char column, unsigned int number)
{
	unsigned char text[4];
	LCD_SetCursor(line, column);
	sprintf(text, "%X", number);
	LCD_ShowString(line, column, text);
}
