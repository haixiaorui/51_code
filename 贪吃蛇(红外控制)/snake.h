#ifndef __SNAKE_H__
#define __SNAKE_H__

extern unsigned char game_run, snake_die, snake_eat_buzzer, snake_die_buzzer;

void PlayGame();
void SnakeMove();
void GameInit();
void SnakeDieKey();

#endif