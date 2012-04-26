/*
 * sharp_sensor.c
 *
 *  Created on: 16 apr 2012
 *      Author: Rickard
 */
#include "sharp_sensor.h"

uint16_t sharpRead()
{
	uint32_t i = 0;
	uint32_t sharpValue;
	for ( i = 0; i < 3; i++ )
	{
		sharpValue = ADCRead( i+5 );

		if( sharpValue >= 50 )
		{
			return sharpValue; //i+5
		}
		else
		{

		}
	}
	return 0;
}

uint32_t sharpReadChannel(uint8_t channel)
{
	uint32_t sharpValue;
	sharpValue = ADCRead( channel );
	if( sharpValue >= 200 )
	{
		return sharpValue;
	}
	return 0;
}
