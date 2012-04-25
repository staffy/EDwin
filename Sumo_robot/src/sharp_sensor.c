/*
 * sharp_sensor.c
 *
 *  Created on: 16 apr 2012
 *      Author: Rickard
 */
#include "sharp_sensor.h"

uint16_t sharpRead()
{
	uint32_t i = 4;
	uint32_t sharpValue[4];
	for ( i = 4; i < 8; i++ )
	{
		sharpValue[i] = ADCRead( i );
		if( sharpValue[i] >= 500 )
		{
			return i;
		}
	}
	return 0;
}

uint32_t sharpReadChannel(uint8_t channel)
{
	uint32_t sharpValue;
	sharpValue = ADCRead( channel );
	if( sharpValue >= 500 )
	{
		return sharpValue;
	}
	return 0;
}
