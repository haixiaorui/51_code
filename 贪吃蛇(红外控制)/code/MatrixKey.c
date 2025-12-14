#include <REGX52.h>
unsigned char Key_KeyNumber;
unsigned char Key()
{
	unsigned char Temp;
	Temp=Key_KeyNumber;
	Key_KeyNumber=0;
	return Temp;
}

unsigned char MatrixKey()
{
	unsigned char KeyNumber=0;
	P1=0xFF;
	P1_2=0;
	if(P1_4==0){KeyNumber=3;}
	P1=0xFF;
	P1_1=0;
	if(P1_5==0){KeyNumber=1;}
	if(P1_4==0){KeyNumber=2;}
	P1=0xFF;
	P1_0=0;
	if(P1_4==0){KeyNumber=4;}
	return KeyNumber;
}

void Loop_MatrixKey()
{
	static unsigned char LastKey=0,NowKey=0;
	LastKey=NowKey;
	NowKey=MatrixKey();
	if(LastKey==0 && NowKey==1){Key_KeyNumber=1;}
	if(LastKey==0 && NowKey==2){Key_KeyNumber=2;}
	if(LastKey==0 && NowKey==3){Key_KeyNumber=3;}
	if(LastKey==0 && NowKey==4){Key_KeyNumber=4;}
}


















