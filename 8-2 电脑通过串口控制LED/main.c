#include <STC89C5xRC.H>
#include "Delay.h"
#include "UART.h"

void main()
{
    Uart1Init();
    while(1)
    {

    }
}

void UART_Routine() interrupt 4
{
	if(RI == 1)
	{
		P2 = ~SBUF;
		UartSendByte(SBUF);
		RI = 0;
	}
}