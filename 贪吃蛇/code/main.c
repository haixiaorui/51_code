/*************************
*名称：51单片机贪吃蛇（普中板子）
*操作方式：按键KeyNum=11上，KeyNum=15下，KeyNum=14左，KeyNum=16右
*作者：科技骨(Bilibil)
*单片机交流QQ群：883948120
**************************/
#include <stdlib.h>
#include <REGX52.H>
#include "HC595.H"
#include "Delay.H"
#include "MatrixKey.H"
#include "Timer0.H"
#include "LCD1602.H"
unsigned char Dire,KeyNum,length,foodx,foody,Speed=30;
char Snakex[40]={0};//蛇身x坐标
char Snakey[40]={0};//蛇身y坐标
unsigned char code Coorx[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
unsigned char code Coory[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
void SnakeMove()//蛇身移动
{	unsigned char i;
    for (i=length+1;i>0;i--)
    {
        Snakex[i]=Snakex[i-1];
        Snakey[i]=Snakey[i-1];
    }	
	switch(Dire)	//Dire：方向（1：左 2：右 3：下 4：上）
	{
		case 1:(Snakex[0])--;if((Snakex[0])<0){(Snakex[0])=7;}break;
		case 2:(Snakex[0])++;(Snakex[0])%=8;break;
		case 3:(Snakey[0])++;(Snakey[0])%=8;break;
		case 4:(Snakey[0])--;if((Snakey[0])<0){(Snakey[0])=7;}break;
	}
}
void Scan_Key()	//检测按键改变方向
{
	if(KeyNum)
	{
		switch(KeyNum)
		{
			case 1:if(Dire!=3)Dire=4;break;
			case 2:if(Dire!=4)Dire=3;break;
			case 3:if(Dire!=2)Dire=1;break;
			case 4:if(Dire!=1)Dire=2;break;
		}
	}
}
void food()//食物坐标
{	
	foodx=(rand()+Snakex[length-1])%8;
	foody=(rand()+Snakex[length-1])%8;
}
void PlaySnakeAC()//刷新蛇、食物动画
{
	unsigned char i;
	for(i=0;i<length;i++)
	{
	MatrixLed(Coorx[Snakex[i]],Coory[Snakey[i]]);
	MatrixLed(Coorx[foodx],Coory[foody]);
	}
}
void Snakedead()//判断死亡，游戏结束
{	unsigned char i;
	for(i=4;i<length;i++)
	{
		if(Snakex[0]==Snakex[i] && Snakey[0]==Snakey[i])//蛇头撞到自己，游戏结束
		{
			P0=0xFF;
			while(1);		
		}
	}
}
void Play_Game()
{	unsigned char i;
	Scan_Key();
	PlaySnakeAC();
	Snakedead();
	for(i=0;i<length;i++)//扫描是否吃到食物
	{	
		if(foodx==Snakex[i] && foody==Snakey[i])
		{
			length++;
			food();
		}
	}
}
void main()
{	
	Timer0_Init();
	length=1;		//初始化长度
	Dire=3;			//初始化方向：下
	while(1)
	{	rand();
		KeyNum=Key();
		Play_Game();
	}
}

void Routine_Timer0()interrupt 1
{
	static unsigned int T0Count1,T0Count2;
	TL0 = 0xCD;		
	TH0 = 0xD4;			
	T0Count1++;
	if(T0Count1>=15)
	{
		T0Count1=0;
		Loop_MatrixKey();
	}
	T0Count2++;
	if(T0Count2>Speed)
	{	
		T0Count2=0;
		SnakeMove();
	}

}













