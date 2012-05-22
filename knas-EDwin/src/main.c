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
#include "drivers/adc.h"
#include "drivers/drive.h"
#include "lineSens.h"

// TODO: insert other definitions and declarations here

void SysTick_Handler()
{
	msTicks++;
}

int main(void) {
 	SysTick_Config( SystemCoreClock/1000 );
	initDrive();
	printf("Hello World\n");
	ADCInit( ADC_CLK );
	
	

	// Enter an infinite loop, just incrementing a counter
	volatile static uint32_t lastRun = 0;
	lastRun = msTicks;
	while(1)
	{
		while(lastRun == msTicks);
		lastRun = msTicks;
		if( !(msTicks%1000) )
		{
			uint32_t values[8];
			int i;
			for(i = 0; i<4; i++)
			{
				values[i] = ADCRead(i);
			}
			values[5] = ADCRead(5);
			values[6] = ADCRead(6);
			//printf("%i: %i   %i: %i   %i: %i   %i: %i   %i: %i   %i: %i\n",0,values[0],1,values[1],2,values[2],3,values[3],5,values[5],6,values[6]);


			char lines[4];
			readLineSensors(lines);
			printf("Line sensors: %i %i %i %i\n",lines[0],lines[1],lines[2],lines[3]);

			setDrive(50,50);
		}


	}
	return 0 ;
}
