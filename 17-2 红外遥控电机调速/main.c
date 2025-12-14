#include <STC89C5xRC.H>
#include "Delay.h"
#include "Key.h"
#include "Nixie.h"
#include "Motor.h"
#include "IR.h"

unsigned char speed, command;

void main()
{
    Motor_Init();
	IR_Init();
    while(1)
    {
		if(IR_GetDataFlag())
		{
			command = IR_GetCommand();
			
			switch(command)
			{
				case IR_0:
					speed = 0;
					break;
				case IR_1:
					speed = 1;
					break;
				case IR_2:
					speed = 2;
					break;
				case IR_3:
					speed = 3;
					break;
			}
			switch(speed)
			{
				case 0:
					Motor_SetSpeed(0);
					break;
				case 1:
					Motor_SetSpeed(50);
					break;
				case 2:
					Motor_SetSpeed(75);
					break;
				case 3:
					Motor_SetSpeed(100);
					break;
			}
		}
		NixieDisp(1, speed);
    }
}

