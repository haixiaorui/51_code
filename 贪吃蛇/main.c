#include <STC89C5xRC.H>
#include "Timer0.h"
#include "snake.h"
#include "MatrixLED.h"
#include "MatrixKey.h"

void main()
{
	Timer0_Init();
    MatrixLED_Init();
	GameInit();
    while(1)
    {
        PlayGame();
    }
}

void Timer0_Routine()	interrupt 1
{
	static unsigned int T0count1, T0count2;
	TH0 = 64535 / 256;
	TL0 = 64535 % 256;
	T0count1++;
	if(T0count1 >= 500)
	{
		T0count1 = 0;
		SnakeMove();
	}
	T0count2++;
	if(T0count2 >= 30)
	{
		T0count2 = 0;
		LoopMatrixKey();
	}
}