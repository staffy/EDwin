/*
===============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Copyright (C)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif

#include <cr_section_macros.h>
#include <NXP/crp.h>
#include "drive.h"
#include "reflex_sensor.h"
#include "gpio.h"

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) {
	//GPIOInit();
	initDrive();
	initReflex();
	GPIOSetDir( 3, 2, 1 );
	GPIOSetValue( 3, 2, 0);
	// Enter an infinite loop, just incrementing a counter
	volatile static int i = 0 ;
	while(1) {
	}
	return 0 ;
}
