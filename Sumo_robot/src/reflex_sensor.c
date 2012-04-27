/*
 * reflex_sensor.c
 *  Created on: 15 mar 2012
 *      Author: Rickard
 */
#include "reflex_sensor.h"
void reflexAnalogInit()
{
	LPC_IOCON->R_PIO0_11 &= ~0x1F;			// - remove bits 0,1 & 2 and pull resistors
	LPC_IOCON->R_PIO0_11 |= 0x02;
	LPC_IOCON->R_PIO1_0 &= ~0x1F;			// - remove bits 0,1 & 2 and pull resistors
	LPC_IOCON->R_PIO1_0 |= 0x02;
	LPC_IOCON->R_PIO1_1 &= ~0x1F;			// - remove bits 0,1 & 2 and pull resistors
	LPC_IOCON->R_PIO1_1 |= 0x02;
	LPC_IOCON->R_PIO1_2 &= ~0x1F;			// - remove bits 0,1 & 2 and pull resistors
	LPC_IOCON->R_PIO1_2 |= 0x02;
	GPIOSetDir( REFLEX_1_PORT, REFLEX_1_BIT, 0 );
	GPIOSetDir( REFLEX_2_PORT, REFLEX_2_BIT, 0 );
	GPIOSetDir( REFLEX_3_PORT, REFLEX_3_BIT, 0 );
	GPIOSetDir( REFLEX_4_PORT, REFLEX_4_BIT, 0 );
	LPC_IOCON->R_PIO0_11   = (1<<6)|(1<<1);      //select AD0
	LPC_IOCON->R_PIO1_0  = (1<<6)|(1<<1);      //select AD1
	LPC_IOCON->R_PIO1_1  = (1<<6)|(1<<1);      //select AD2
	LPC_IOCON->R_PIO1_2  = (1<<6)|(1<<1);      //select AD3
}

uint32_t reflexReadAnalog()
{
	uint32_t i = 0;
	uint32_t reflexValue;
	for ( i = 0; i < 4; i++ )
	{
		reflexValue = ADCRead( i );

		//Correct, switch dir at white
		if( reflexValue <= 850 )
		{
			return i; //i+5
		}
		//Inverterted, switch dir at black
		if( reflexValue >= 950 )
		{
			return i; //i+5
		}
	}
	return 4;
}

void reflexDigitalInit()
{
	LPC_IOCON->R_PIO0_11 &= ~0x1F;			// - remove bits 0,1 & 2 and pull resistors
	LPC_IOCON->R_PIO0_11 |= 0x01;
	LPC_IOCON->R_PIO1_0 &= ~0x1F;			// - remove bits 0,1 & 2 and pull resistors
	LPC_IOCON->R_PIO1_0 |= 0x01;
	LPC_IOCON->R_PIO1_1 &= ~0x1F;			// - remove bits 0,1 & 2 and pull resistors
	LPC_IOCON->R_PIO1_1 |= 0x01;
	LPC_IOCON->R_PIO1_2 &= ~0x1F;			// - remove bits 0,1 & 2 and pull resistors
	LPC_IOCON->R_PIO1_2 |= 0x01;
	GPIOSetDir( REFLEX_1_PORT, REFLEX_1_BIT, 0 );
	GPIOSetDir( REFLEX_2_PORT, REFLEX_2_BIT, 0 );
	GPIOSetDir( REFLEX_3_PORT, REFLEX_3_BIT, 0 );
	GPIOSetDir( REFLEX_4_PORT, REFLEX_4_BIT, 0 );
}

uint32_t reflexReadDigital()
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
