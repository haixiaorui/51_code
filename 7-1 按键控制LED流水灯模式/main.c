#include <STC89C5xRC.H>
#include <INTRINS.H>
#include "Timer0.h"
#include "key.h"

unsigned char KeyNum, LEDMode;

void main()
{
	P2 = 0xfe;
    Timer0_Init();
    while(1)
    {
        KeyNum = Key();
		if(KeyNum == 1) 
		{
			LEDMode++;
			LEDMode %= 2;
		}
    }
}

void Timer0_Routine()	interrupt 1
{
	static unsigned int T0count;
	TH0 = 64535 / 256;
	TL0 = 64535 % 256;
	T0count++;
	if(T0count >= 500)
	{
		T0count = 0;
		if(LEDMode == 0)
		{
			P2 = _crol_(P2, 1);
		}
		if(LEDMode == 1)
		{
			P2 = _cror_(P2, 1);
		}
	}
}