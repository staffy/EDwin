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


//just for blinky
#include "clkconfig.h"
#include "config.h"
#include "timer32.h"

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
#define START_PORT 0	// Port for start
#define START_BIT 1		// Bit on port for start
#define KILL_SWITCH_PORT 0	// Port for kill_switch
#define KILL_SWITCH_BIT 3	// Pin on port for kill_switch


int main(void)
{
	GPIOInit();
	//SysTick_Config( SystemCoreClock/1000 );
	//SysTick->CTRL &= (0 << 1); 	// Need to be commected for lcd
	initDrive();
	//ADCInit( ADC_CLK );
	//LCD_init();
	//initReflex();
	//GPIOSetDir( 3, 2, 1 );
	//GPIOSetValue( 3, 2, 0);
	GPIOSetDir( LED_PORT, LED_BIT, 1 );
	GPIOSetValue( LED_PORT, LED_BIT, LED_OFF );
	GPIOSetDir( 3, 2, 1 );
	GPIOSetDir( START_PORT, START_BIT, 0);
	GPIOSetDir( KILL_SWITCH_PORT, KILL_SWITCH_BIT, 0);
	// Enter an infinite loop, just incrementing a counter
	//LCD_home();
	//LCD_clear();
	//LCD_sendStr("Init done!");

	init_timer32(0, TIME_INTERVAL);
	enable_timer32(0);

	while(1)
	{
			//GPIOSetValue( LED_PORT, LED_BIT, LED_OFF );
			//uint16_t adcValue = ADCRead( 5 );
			/*if(reflexRead())//adcValue > 100)
			{
				GPIOSetValue( LED_PORT, LED_BIT, LED_OFF );
			}
			else
			{
				GPIOSetValue( LED_PORT, LED_BIT, LED_ON );
			}*/


		//-----MAIN-----//
//Start signal: 0, Kill switch: 1, LED: off -> POWER ON
		while(!GPIOReadValue(START_PORT, START_BIT) && GPIOReadValue(KILL_SWITCH_PORT, KILL_SWITCH_BIT))//while not start signal and kill switch signal
		{
			//LED = släckt
			GPIOSetValue( LED_PORT, LED_BIT, LED_OFF );
			//do nothing
		}


//Start signal: 1, Kill switch: 1, LED: on -> STARTED
			//enable_engines();//gör nåt annat smart!
		while(GPIOReadValue(START_PORT, START_BIT) && GPIOReadValue(KILL_SWITCH_PORT, KILL_SWITCH_BIT))//while not stop
		{
			//LED = TÄND
			GPIOSetValue( LED_PORT, LED_BIT, LED_ON );
	/*		switch(reflexRead())
			{
				case 0:
					set_movement(1, 60);//backwards
					break;
				case 1:
					set_movement(1, 60);//backwards
					break;
				case 2:
					set_movement(0, 60);//forward
					break;
				case 3:
					set_movement(0, 60);//forward
					break;
				case 4:
					set_movement(2, 60);//turn right
					//if object found in front
					if(1)//if(sharpRead() == 4 || sharpRead == 5)
					{
						set_movement(0, 60);//forward
					}
					//if object found behind
					if(2)//if(sharpRead() == 1 || sharpRead() == 2)
					{
						set_movement(1, 60);//backwards
					}
					break;
				default:
					break;
				}*/
		}

//Start signal: 0, Kill switch: 0, LED: flashing -> STOPPED
		while(!GPIOReadValue(START_PORT, START_BIT) && !GPIOReadValue(KILL_SWITCH_PORT, KILL_SWITCH_BIT))
		{
				if ( (timer32_0_counter%LED_TOGGLE_TICKS) < (LED_TOGGLE_TICKS/2) )
				{
					GPIOSetValue( LED_PORT, LED_BIT, LED_OFF );
				}
				else
				{
	  			  GPIOSetValue( LED_PORT, LED_BIT, LED_ON );
				}
				/* Go to sleep to save power between timer interrupts */
				__WFI();

				//disable_engines();
		}
	}
	return 0 ;
}
