#include <STC89C5xRC.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char KeyNum;
unsigned int password, count;

void main()
{
	LCD_Init();
	LCD_ShowString(1, 1, "PassWord:");
	while(1)
	{
		KeyNum = KeyDown();
		if(KeyNum) {
			if(KeyNum <= 10 && count < 4)	// S1~S10: 输入密码
			{
				password *= 10;		// 密码左移一位
				password += KeyNum % 10;
				count++;
				LCD_ShowNum(2, 1, password, 4);
			}
			if(KeyNum == 11)	// S11: 确认密码是否正确
			{
				if(password == 2345)
				{
					LCD_ShowString(1, 14, "OK ");
				}
				else
				{
					LCD_ShowString(1, 14, "ERR");
				}
				password = 0;
				count = 0;
				LCD_ShowNum(2, 1, password, 4);
			}
			if(KeyNum == 12)	// S12：退格
			{
				password /= 10;
				if(count != 0) count--;
				LCD_ShowNum(2, 1, password, 4);
			}
		}
	}
} 