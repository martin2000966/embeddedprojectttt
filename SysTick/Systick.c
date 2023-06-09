#include "TM4C123GH6PM.h"
#include <stdint.h>
#include <string.h>

void SysTick_Init(){
	NVIC_ST_CTRL_R = NVIC_ST_CTRL_R & ~(0x00000001);
	NVIC_ST_RELOAD_R = 8000000-1;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R |= 0x5;
	while((NVIC_ST_CTRL_R & 0x00010000) == 0){};
}

void Delay(uint32_t x){
	uint32_t i;
	for(i=0;i<x;i++)
	{
		SysTick_Init();
	}
}
