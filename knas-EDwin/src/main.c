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


void SysTick_Handler(void)
{
	msTicks++;
}
int main(void)
{
	SysTick_Config( SystemCoreClock/1000 );
	msTicks = 0;
	printf("EDwin started\n");

	// Enter an infinite loop, just incrementing a counter
	volatile static int lastRun = 0 ;
	while(1)
	{
		while(lastRun == msTicks); // Wait for msTicks to inc.
		lastRun = msTicks;

		if( !(msTicks % 1000))
		{
			printf("%i\n",msTicks);
		}
		lastRun = msTicks;
	}
	return 0 ;
}
