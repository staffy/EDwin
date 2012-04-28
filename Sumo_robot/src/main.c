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
#include <stdlib.h>
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
#define SPEED_0 20
#define SPEED_1 40
#define SPEED_2 60
#define SPEED_3 80
#define SPEED_4 100
#define SPEED SPEED_4

int main(void)
{
	//GPIOInit();
	SysTick_Config( SystemCoreClock/1000 );
	//SysTick->CTRL &= (0 << 1); 	// Need to be commented for lcd
	initDrive();
	ADCInit( ADC_CLK );
	reflexAnalogInit();
	//sharpInit();
	//reflexDigitalInit();
	//LCD_init();
	//initReflex();
	GPIOSetDir( LED_PORT, LED_BIT, 1 );
	GPIOSetValue( LED_PORT, LED_BIT, LED_OFF );
	//GPIOSetDir( 3, 2, 1 );
	GPIOSetDir( START_PORT, START_BIT, 0);
	GPIOSetDir( KILL_SWITCH_PORT, KILL_SWITCH_BIT, 0);

	while(1)
	{

		//-----MAIN-----//
		//Start signal: 0, Kill switch: 1, LED: off -> POWER ON
		while(!GPIOReadValue(START_PORT, START_BIT) && GPIOReadValue(KILL_SWITCH_PORT, KILL_SWITCH_BIT))//while not start signal and kill switch signal
		{
			//LED = släckt
			GPIOSetValue( LED_PORT, LED_BIT, LED_OFF );
			set_movement(0,0);
			//do nothing
		}


		//Start signal: 1, Kill switch: 1, LED: on -> STARTED
		//enable_engines();//gör nåt annat smart!
		//uint32_t sharp;
		set_movement(1, SPEED);//backwards
		while(GPIOReadValue(START_PORT, START_BIT) && GPIOReadValue(KILL_SWITCH_PORT, KILL_SWITCH_BIT))//while not stop
		{
			//LED = TÄND
			GPIOSetValue( LED_PORT, LED_BIT, LED_ON );

			switch(reflexReadAnalog())
			{
			case 0:
				set_movement(1, SPEED);//backwards
				break;
			case 1:
				set_movement(1, SPEED);//backwards
				break;
			case 2:
				set_movement(0, SPEED);//forward
				break;
			case 3:
				set_movement(0, SPEED);//forward
				break;
			case 4:
				//set_movement(2, SPEED);//turn right
				//if object found in front
				/*
					sharp = sharpReadMean();
					if(sharp == 5 || sharp == 6)
					{
						set_movement(0, SPEED);//forward
					}
					//if object found behind
					else if(sharp == 7)
					{
						set_movement(1, SPEED); //backwards
					}
					else
					{
						set_movement(2, SPEED);//turn left
					}
				 */
				break;

			default:
				break;
			}
		}

		//Start signal: 0, Kill switch: 0, LED: flashing -> STOPPED
		while(!GPIOReadValue(START_PORT, START_BIT) && !GPIOReadValue(KILL_SWITCH_PORT, KILL_SWITCH_BIT))
		{
			set_movement(0,0);
		}
	}
	return 0 ;
}
