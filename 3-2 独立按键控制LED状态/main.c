#include <STC89C5xRC.H>
#include <INTRINS.H>

void Delayms(unsigned int ms)	//@11.0592MHz
{
	unsigned char data i, j;
	while(ms--)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}


void main()
{
	while(1)
	{
		if(P31 == 0) {
			Delayms(20);
			while(P31 == 0);
			Delayms(20);
			
			P20 = ~P20;
		}
	}
}