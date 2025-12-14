#ifndef __LCD1602_H__
#define __LCD1602_H__

void LCD_Init(void);
void LCD_ShowChar(unsigned char line, unsigned char column, unsigned char Char);
void LCD_ShowString(unsigned char line, unsigned char column, unsigned char* String);
void LCD_ShowNum(unsigned char line, unsigned char column, unsigned int number);
void LCD_ShowSignedNum(unsigned char line, unsigned char column, int number);
void LCD_ShowHexNum(unsigned char line, unsigned char column, unsigned int number);

#endif