/*
 * reflex_sensor.c
 *  Created on: 15 mar 2012
 *      Author: Rickard
 */
#include "reflex_sensor.h"

void reflexInit()
{
	GPIOSetDir( REFLEX_1_PORT, REFLEX_1_BIT, 0 );
	GPIOSetDir( REFLEX_2_PORT, REFLEX_2_BIT, 0 );
	GPIOSetDir( REFLEX_3_PORT, REFLEX_3_BIT, 0 );
	GPIOSetDir( REFLEX_4_PORT, REFLEX_4_BIT, 0 );

	LPC_IOCON->R_PIO0_11 &= ~0x1F;		// - remove bits 0,1 & 2 and pull resistors
	LPC_IOCON->R_PIO1_0 &= ~0x1F;			// - remove bits 0,1 & 2 and pull resistors
	LPC_IOCON->R_PIO1_1 &= ~0x1F;			// - remove bits 0,1 & 2 and pull resistors
	LPC_IOCON->R_PIO1_2 &= ~0x1F;			// - remove bits 0,1 & 2 and pull resistors
}

uint16_t reflexRead()
{
	if(!GPIOReadValue(REFLEX_1_PORT, REFLEX_1_BIT))
	{
		return 0;
	}
	else if(!GPIOReadValue(REFLEX_2_PORT, REFLEX_2_BIT))
	{
		return 1;
	}
	else if(!GPIOReadValue(REFLEX_3_PORT, REFLEX_3_BIT))
	{
		return 2;
	}
	else if(!GPIOReadValue(REFLEX_4_PORT, REFLEX_4_BIT))
	{
		return 3;
	}
	else
	{
		return 4;
	}
}
