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
	//printf("Hello World\n");
	ADCInit( ADC_CLK );
	
	

	// Enter an infinite loop, just incrementing a counter
	volatile static uint32_t lastRun = 0;
	lastRun = msTicks;
	while(1)
	{
		while(lastRun == msTicks);
		lastRun = msTicks;
		if( !(msTicks%60) )
		{
			char lines[4], sharp[2];
			readLineSensors(lines);
			readSharpSensors(sharp);
			//printf("Line sensors: %i %i %i %i \nSharp Sensors: %i %i\n\n",lines[0],lines[1],lines[2],lines[3],sharp[0],sharp[1]);

			if(sharp[0] && sharp[1])
			{
				setDrive(100, 0);
			}
			else if(sharp[1])
			{
				setDrive(80, -50);
			}
			else if(sharp[0])
			{
				setDrive(80, 50);
			}
			else
			{
				setDrive(0, -20);
			}
		}


	}
	return 0 ;
}
