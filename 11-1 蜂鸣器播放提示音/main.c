#include <STC89C5xRC.H>
#include "key.h"
#include "Nixie.h"
#include "Buzzer.h"

unsigned char KeyNum;

void main()
{
    NixieDisp(1, 0);
    while(1)
    {
        KeyNum = Key();
		if(KeyNum)
		{
			BuzzerTime(100);
			NixieDisp(1, KeyNum);
		}
    }
}