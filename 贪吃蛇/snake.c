#include <stdlib.h>
#include <STC89C5xRC.H>
#include "MatrixLED.h"
#include "MatrixKey.h"

unsigned char snakeX[40] = {1};
unsigned char snakeY[40] = {1};

unsigned char snake_size, snake_dir, KeyNum, foodX, foodY;

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
		}
	}
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
	}
}

void SnakeDie()
{
	unsigned char i;
	for(i = 4; i < snake_size; i++) {
		if(snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
			P0 = 0xff;
			while(1);
		}
	}
}

void GameInit()
{
	snake_size = 2;
	snake_dir = 2;
	FoodCreate();
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