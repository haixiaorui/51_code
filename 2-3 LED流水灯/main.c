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
	unsigned char i;
	while(1)
	{
		P2 = 0xfe;
		i = 8;
		while(i--) {
			Delayms(200);
			P2 = ~((~P2) << 1);
		}
	}
}