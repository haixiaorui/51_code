#include <STC89C5xRC.H>
#include "Delay.h"
#include "Timer0.h"

sbit buzzer = P2^5;

#define P 0 // 休止符
// 低音
#define L1 1
#define L2 2
#define L3 3
#define L4 4
#define L5 5
#define L6 6
#define L7 7
// 中音
#define M1 8
#define M2 9
#define M3 10
#define M4 11
#define M5 12
#define M6 13
#define M7 14
// 高音
#define H1 15
#define H2 16
#define H3 17
#define H4 18
#define H5 19
#define H6 20
#define H7 21

#define SPEED 500

unsigned int FreqTable[] = {
	0,
    // 低音区 (Low Octave)
    63628,  // 低音 1 (C)
    63835,  // 低音 2 (D)
    64021,  // 低音 3 (E)
    64103,  // 低音 4 (F)
    64260,  // 低音 5 (G)
    64400,  // 低音 6 (A)
    64524,  // 低音 7 (B)
    
    // 中音区 (Middle Octave)
    64580,  // 中音 1 (C)
    64671,  // 中音 2 (D)
    64777,  // 中音 3 (E)
    64820,  // 中音 4 (F)
    64898,  // 中音 5 (G)
    64968,  // 中音 6 (A)
    65030,  // 中音 7 (B)
    
    // 高音区 (High Octave)
    65058,  // 高音 1 (C)
    65110,  // 高音 2 (D)
    65157,  // 高音 3 (E)
    65178,  // 高音 4 (F)
    65217,  // 高音 5 (G)
    65252,  // 高音 6 (A)
    65283   // 高音 7 (B)
};

unsigned char Music[] = {
	M1, 4,
	M1, 4,
	M5, 4,
	M5, 4,
	M6, 4,
	M6, 4,
	M5, 8,
	M4, 4,
	M4, 4,
	M3, 4,
	M3, 4,
	M2, 4,
	M2, 4,
	M1,	8,
	0xff
};

unsigned char freqSelect, musicSelect;

void main()
{
    Timer0_Init();
    while(1)
    {
		if(Music[musicSelect] != 0xff)
		{
			freqSelect = Music[musicSelect];
			musicSelect++;
			Delayms(SPEED/4 * Music[musicSelect]);
			musicSelect++;
			TR0 = 0;
			Delayms(5);
			TR0 = 1;
		}
		else
		{
			TR0 = 0;
			while(1);
		}
    }
}

void Timer0_Routine()	interrupt 1
{
	if(FreqTable[freqSelect])
	{
		TH0 = FreqTable[freqSelect] / 256;
		TL0 = FreqTable[freqSelect] % 256;
		buzzer = !buzzer;
	}
}