#include <STC89C5xRC.H>
#include "Timer0.h"
#include "Int0.h"

unsigned int IR_time;
unsigned char IR_state;

unsigned char IR_data[4];
unsigned char IR_pData;

unsigned char IR_dataFlag;
unsigned char IR_repeatFlag;
unsigned char IR_address;
unsigned char IR_command;

void IR_Init(void)
{
	Timer0_Init();
	Int0_Init();
}

unsigned char IR_GetDataFlag(void)
{
	if(IR_dataFlag)
	{
		IR_dataFlag = 0;
		return 1;
	}
	return 0;
}

unsigned char IR_GetRepeatFlag(void)
{
	if(IR_repeatFlag)
	{
		IR_repeatFlag = 0;
		return 1;
	}
	return 0;
}

unsigned char IR_GetAddress(void)
{
	return IR_address;
}

unsigned char IR_GetCommand(void)
{
	return IR_command;
}

void Int0_Routine(void) interrupt 0
{
	if(IR_state == 0)
	{
		Timer0_SetCounter(0);
		Timer0_Run(1);
		IR_state = 1;
	}
	else if(IR_state == 1)
	{
		IR_time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		if(IR_time > 12442 - 500 && IR_time < 12442 + 500)
		{
			IR_state = 2;
		}
		else if(IR_time > 10368 - 500 && IR_time < 10368 + 500)
		{
			IR_repeatFlag = 1;
			Timer0_Run(0);
			IR_state = 0;
		}
		else
		{
			IR_state = 1;
		}
	}
	else if(IR_state == 2)
	{
		IR_time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		if(IR_time > 1120 - 500 && IR_time < 1120 + 500)
		{
			IR_data[IR_pData / 8] &= ~(0x01 << (IR_pData % 8));
			IR_pData++;
		}
		else if(IR_time > 2250 - 500 && IR_time < 2250 + 500)
		{
			IR_data[IR_pData / 8] |= (0x01 << (IR_pData % 8));
			IR_pData++;
		}
		else
		{
			IR_pData = 0;
			IR_state = 1;
		}
		if(IR_pData >= 32)
		{
			IR_pData = 0;
			if((IR_data[0] == ~IR_data[1]) && (IR_data[2] == ~IR_data[3]))
			{
				IR_address = IR_data[0];
				IR_command = IR_data[2];
				IR_dataFlag = 1;
			}
			Timer0_Run(0);
			IR_state = 0;
		}
	}
}