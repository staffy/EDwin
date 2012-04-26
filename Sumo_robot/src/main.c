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
#include "adc.h"
#include "drive.h"
#include "reflex_sensor.h"
#include "sharp_sensor.h"
#include "gpio.h"
#include "LCD.h"



// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

// TODO: insert other include files here

// TODO: insert other definitions and declarations here
#define LED_PORT 0		// Port for led
#define LED_BIT 7		// Bit on port for led
#define LED_ON 1		// Level to set port to turn on led
#define LED_OFF 0		// Level to set port to turn off led


int main(void) {
	//GPIOInit();
	SysTick_Config( SystemCoreClock/1000 );
	//SysTick->CTRL &= (0 << 1); 	// Need to be commected for lcd
	initDrive();
	ADCInit( ADC_CLK );
	//LCD_init();
	//initReflex();
	//GPIOSetDir( 3, 2, 1 );
	//GPIOSetValue( 3, 2, 0);
	GPIOSetDir( LED_PORT, LED_BIT, 1 );
	GPIOSetValue( LED_PORT, LED_BIT, LED_ON );
	GPIOSetDir( 3, 2, 1 );
	// Enter an infinite loop, just incrementing a counter
	//LCD_home();
	//LCD_clear();
	//LCD_sendStr("Init done!");
	while(1)
	{
		GPIOSetValue( LED_PORT, LED_BIT, LED_ON );
		//uint16_t adcValue = ADCRead( 5 );
		if(reflexRead())//adcValue > 100)
		{
			GPIOSetValue( LED_PORT, LED_BIT, LED_OFF );
		}
		else
		{
			GPIOSetValue( LED_PORT, LED_BIT, LED_ON );
		}
	}
	return 0 ;
}
