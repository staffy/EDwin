/*
 * reflex_sensor.c
 *  Created on: 15 mar 2012
 *      Author: Rickard
 */
#include "reflex_sensor.h"

uint16_t reflexRead()
{
	uint32_t i = 0;
	//for ( i = 0; i < REFLEX_NUM; i++ )
	//{
		reflexValue[i] = ADCRead( 5 );
		if( reflexValue[i] >= 500 )
		{
			return 1;
		}
	//}
	return 0;
}

void initReflex()		// Enables interrupt on Port0 bit2
{
	/*LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 6);		// Enable clock for GPIO
	NVIC_EnableIRQ(EINT0_IRQn);					// Enable external interrupt
	LPC_GPIO0->DIR &= ~(1 << 2);        		// Port0 bit2 input
	LPC_GPIO0->IS &= ~(1 << 2);					// Trigger on edge
	LPC_GPIO0->IBE |= (1 << 2);					// Trigger on double edge
	LPC_GPIO0->IEV |= (1 << 2);					// int on 5v pos edge
	LPC_GPIO0->IE |= (1 << 2);					// Enable interrupt
	return;
	 */
	/* use as input event, interrupt test. */
	/*
	GPIOSetDir( PORT2, 0, 0 );
	GPIOSetDir( PORT2, 1, 0 );
	GPIOSetDir( PORT3, 0, 0 );
	GPIOSetDir( PORT3, 1, 0 );
	*/
	/* single edge trigger, active high. */
	/*GPIOSetInterrupt( PORT2, 0, 0, 0, 0 );
	GPIOSetInterrupt( PORT2, 1, 0, 0, 0 );
	GPIOSetInterrupt( PORT2, 0, 0, 0, 0 );
	GPIOSetInterrupt( PORT2, 1, 0, 0, 0 );*/
	//Enable interrupts
	/*
	GPIOIntEnable( PORT2, 0 );
	GPIOIntEnable( PORT2, 1 );
	GPIOIntEnable( PORT3, 0 );
	GPIOIntEnable( PORT3, 1 );*/
}
/*
void PIOINT0_IRQHandler(void)		// Front sensors
{
	set_movement(1);
	//GPIOSetValue( 3, 2, 1);
	LPC_GPIO0->IC |= (1 << 2); 	// reset interrupt flag
	//GPIOIntClear( PORT2, 0 );
	//GPIOIntClear( PORT2, 1 );
	return;
}
void PIOINT2_IRQHandler(void)		// Front sensors
{
	set_movement(1);
	//GPIOSetValue( 3, 2, 1);
	LPC_GPIO2->IC |= (1 << 2); 	// reset interrupt flag
	//GPIOIntClear( PORT2, 0 );
	//GPIOIntClear( PORT2, 1 );
	return;
}

void PIOINT3_IRQHandler(void)		// back sensors
{
	set_movement(0);
	//LPC_GPIO3->IC |= (1 << 2); 	// reset interrupt flag
	//GPIOIntClear( PORT3, 0 );
	//GPIOIntClear( PORT3, 1 );
	return;
}

//void

*/
