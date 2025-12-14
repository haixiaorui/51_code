#include <STC89C5xRC.H>
#include "Delay.h"

unsigned char Loop_KeyNumber;

unsigned char Key(void)
{
	unsigned char temp = 0;
	temp = Loop_KeyNumber;
	Loop_KeyNumber = 0;
	return temp;
}

unsigned char Key_GetState()
{
	unsigned char KeyNumber = 0;
	
	if(P31 == 0) KeyNumber = 1;
	if(P30 == 0) KeyNumber = 2;
	if(P32 == 0) KeyNumber = 3;
	if(P33 == 0) KeyNumber = 4;
	
	return KeyNumber;
}

void Key_Loop(void)
{
	static unsigned char nowState, lastState;
	lastState = nowState;
	nowState = Key_GetState();
	if(lastState == 0 && nowState == 1)
	{
		Loop_KeyNumber = 1;
	}
	if(lastState == 0 && nowState == 2)
	{
		Loop_KeyNumber = 2;
	}
	if(lastState == 0 && nowState == 3)
	{
		Loop_KeyNumber = 3;
	}
	if(lastState == 0 && nowState == 4)
	{
		Loop_KeyNumber = 4;
	}
}