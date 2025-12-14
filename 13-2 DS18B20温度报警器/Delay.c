
void Delayms(unsigned int ms)
{
	unsigned char data i, j;
	while(ms--)
	{
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}