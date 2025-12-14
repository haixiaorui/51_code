#include <STC89C5xRC.H>
#include "Delay.h"
#include "Nixie.h"

void main()
{
	unsigned char i;
	while(1)
	{
		for(i = 1; i <= 8; i++) {
			NixieDisp(i, i);
		}
	}
}