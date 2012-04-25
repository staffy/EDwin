/*
 * reflex_sensor.c
 *  Created on: 15 mar 2012
 *      Author: Rickard
 */
#include "reflex_sensor.h"

uint16_t reflexRead()
{
	uint32_t i = 4;
	for ( i = 4; i <= 5; i++ )
	{
		reflexValue[i] = ADCRead( i );
		if( reflexValue[i] >= 500 )
		{
			return 1;
		}
	}
	return 0;
}
