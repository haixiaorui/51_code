#include <stdlib.h>
#include <STC89C5xRC.H>
#include "MatrixLED.h"
#include "IR.h"

unsigned char snakeX[40] = {1};
unsigned char snakeY[40] = {1};

unsigned char snake_size, snake_dir, KeyNum, foodX, foodY;
unsigned char game_run, snake_die, snake_eat_buzzer, snake_die_buzzer;

void FoodCreate();

void GameInit()
{
	snake_size = 2;
	snake_dir = 2;
	snakeX[0] = 1;
	snakeY[0] = 1;
	FoodCreate();
	game_run = 1;
}

void SnakeLedShow(unsigned char x, unsigned char y)
{
	switch(x)
	{
		case 1:
			MatrixLED_ShowColumn(y-1, 0x80);
			break;
		case 2:
			MatrixLED_ShowColumn(y-1, 0x40);
			break;
		case 3:
			MatrixLED_ShowColumn(y-1, 0x20);
			break;
		case 4:
			MatrixLED_ShowColumn(y-1, 0x10);
			break;
		case 5:
			MatrixLED_ShowColumn(y-1, 0x08);
			break;
		case 6:
			MatrixLED_ShowColumn(y-1, 0x04);
			break;
		case 7:
			MatrixLED_ShowColumn(y-1, 0x02);
			break;
		case 8:
			MatrixLED_ShowColumn(y-1, 0x01);
			break;
	}
}

void PlayDraw()
{
	unsigned char i;
	for(i = 0; i < snake_size; i++) {
		SnakeLedShow(snakeX[i], snakeY[i]);
	}
	SnakeLedShow(foodX, foodY);
}

void SnakeMove()
{
	unsigned char i;
	// 0 1 2 3 上 右 下 左
	for(i = snake_size-1; i > 0; i--) {
		snakeX[i] = snakeX[i-1];
		snakeY[i] = snakeY[i-1];
	}
	switch(snake_dir)
	{
		case 0:
			snakeX[0]--;
			if(snakeX[0] < 1) snakeX[0] = 8;
			break;
		case 1:
			snakeY[0]++;
			if(snakeY[0] > 8) snakeY[0] = 1;
			break;
		case 2:
			snakeX[0]++;
			if(snakeX[0] > 8) snakeX[0] = 1;
			break;
		case 3:
			snakeY[0]--;
			if(snakeY[0] < 1) snakeY[0] = 8;
			break;
	}
}

unsigned char command;

unsigned char Key()
{
	unsigned char key = 0;
	if(IR_GetDataFlag())
	{
		command = IR_GetCommand();
		if(command == IR_2) 	key = 1;
		if(command == IR_8) 	key = 2;
		if(command == IR_4) 	key = 3;
		if(command == IR_6) 	key = 4;
		if(command == IR_5) 	key = 5;
		if(command == IR_POWER) key = 6;
	}
	return key;
}

void ScanKey()
{
	if(KeyNum)
	{
		switch(KeyNum)
		{
			case 1:
				if(snake_dir != 2) snake_dir = 0;
				break;
			case 2:
				if(snake_dir != 0) snake_dir = 2;
				break;
			case 3:
				if(snake_dir != 1) snake_dir = 3;
				break;
			case 4:
				if(snake_dir != 3) snake_dir = 1;
				break;
			case 5:
				game_run = !game_run;
				break;
			case 6:
				if(snake_die)
				{
					GameInit();
					snake_die = 0;
				}
				break;
		}
	}
}

void SnakeDieKey()
{
	KeyNum = Key();
	ScanKey();
}

void FoodCreate()
{
	foodX = ((rand()+snakeX[snake_size-1])%8)+1;
	foodY = ((rand()+snakeY[snake_size-1])%8)+1;
}

void EatFood()
{
	if(snakeX[0] == foodX && snakeY[0] == foodY)
	{
		snake_size++;
		FoodCreate();
		snake_eat_buzzer = 1;
	}
}

void SnakeDie()
{
	unsigned char i;
	for(i = 4; i < snake_size; i++) {
		if(snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
			snake_die_buzzer = 1;
			P0 = 0xff;
			snake_die = 1;
		}
	}
}


void PlayGame()
{
	unsigned char i;
	rand();
	ScanKey();
	PlayDraw();
	SnakeDie();
	EatFood();
	KeyNum = Key();
	for(i = 0; i < snake_size; i++) {
		if(foodX == snakeX[i] && foodY == snakeY[i]) {
			FoodCreate();
		}
	}
}