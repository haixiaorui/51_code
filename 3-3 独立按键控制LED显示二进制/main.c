#include <STC89C5xRC.H>
#include <INTRINS.H>

void Delayms(unsigned int ms)
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
	unsigned char i = 0;
	while(1)
	{
		if(P31 == 0) {
			Delayms(20);
			while(P31 == 0);
			Delayms(20);
			
			i++;
			P2 = ~i;
		}
	}
}