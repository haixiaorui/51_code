#include <STC89C5xRC.H>
#include "Timer1.h"
#include "snake.h"
#include "MatrixLED.h"
#include "IR.h"

sbit buzzer = P2^5;

void main()
{
	Timer1_Init();
	IR_Init();
    MatrixLED_Init();
	GameInit();
    while(1)
    {
		if(!snake_die)
			PlayGame();
		else
			SnakeDieKey();
    }
}

void Timer1_Routine()	interrupt 3
{
	static unsigned int T1count1, T1count2, T1count3;
	TH1 = 64535 / 256;
	TL1 = 64535 % 256;
	T1count1++;
	if(T1count1 >= 500)
	{
		T1count1 = 0;
		if(game_run && !snake_die)
			SnakeMove();
	}
	if(snake_eat_buzzer)
	{
		T1count2++;
		buzzer = !buzzer;
		if(T1count2 >= 200)
		{
			T1count2 = 0;
			snake_eat_buzzer = 0;
		}
	}
	if(snake_die_buzzer)
	{
		T1count3++;
		buzzer = !buzzer;
		if(T1count3 >= 1000)
		{
			T1count3 = 0;
			snake_die_buzzer = 0;
		}
	}
}