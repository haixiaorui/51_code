#include <STC89C5xRC.H>
#include "Delay.h"

sbit RCK = P3^5;	// RCLK
sbit SCK = P3^6;	// SRCLK
sbit SER = P3^4;	// SER

#define MATRIX_LED_PORT P0

/**
   * @brief  74HC595写入一个字节
   * @param	 要写入的字节
   * @retval 无
   */
void _74HC595_WriteByte(unsigned char byte)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		SER = byte & (0x80 >> i);
		SCK = 1;
		SCK = 0;
	}
	RCK = 1;
	RCK = 0;
}

/**
   * @brief  LED点阵屏显示一列数据
   * @param  column：要选择的列，范围：0~7，0在最左边
   * @param  Data：选择列显示的数据，高位在上，1为亮，0为灭
   * @retval 无
   */
void MatrixLED_ShowColumn(unsigned char column, unsigned char Data)
{
	_74HC595_WriteByte(Data);
	MATRIX_LED_PORT = ~(0x80 >> column);
	Delayms(1);
	MATRIX_LED_PORT = 0xFF;
}

void main()
{
    SCK = 0;
	RCK = 0;
    while(1)
    {
        MatrixLED_ShowColumn(0, 0x38);
		MatrixLED_ShowColumn(1, 0x7C);
		MatrixLED_ShowColumn(2, 0x7E);
		MatrixLED_ShowColumn(3, 0x3F);
		MatrixLED_ShowColumn(4, 0x3F);
		MatrixLED_ShowColumn(5, 0x7E);
		MatrixLED_ShowColumn(6, 0x7C);
		MatrixLED_ShowColumn(7, 0x38);
    }
}