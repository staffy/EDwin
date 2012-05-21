/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

#include <stdio.h>
#include "variables.h"

// TODO: insert other definitions and declarations here

void SysTick_Handler()
{
	msTicks++;
}

int main(void) {
	SysTick_Config( SystemCoreClock/1000 );
	printf("Hello World\n");
	
	
	// Enter an infinite loop, just incrementing a counter
	volatile static uint32_t lastRun = 0;
	lastRun = msTicks;
	while(1)
	{
		while(lastRun == msTicks);
		lastRun = msTicks;
		if( !(msTicks%2000) )
		{
			printf("%i\n",msTicks);
		}


	}
	return 0 ;
}
