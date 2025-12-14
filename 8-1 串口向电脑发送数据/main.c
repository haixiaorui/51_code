#include <STC89C5xRC.H>
#include "Delay.h"
#include "UART.h"

unsigned char sec;

void main()
{
    Uart1Init();
    while(1)
    {
        UartSendByte(sec);
		sec++;
		Delayms(1000);
    }
}