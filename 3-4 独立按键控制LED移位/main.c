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
	P2 = 0xfe;
	while(1)
	{
		if(P31 == 0) {
			Delayms(20);
			while(P31 == 0);
			Delayms(20);
			
			P2 = ~((~P2) >> 1);
			if(P2 == 0xff) P2 = 0x7f;
		}
		
		if(P30 == 0) {
			Delayms(20);
			while(P30 == 0);
			Delayms(20);
			
			P2 = ~((~P2) << 1);
			if(P2 == 0xff) P2 = 0xfe;
		}
	}
}