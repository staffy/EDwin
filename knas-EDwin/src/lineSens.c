/*
 * lineSens.c
 *
 *  Created on: 22 maj 2012
 *  Author: staffan
 *  Contains the code for interfacing the line sensors
 */
#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif

#include "lineSens.h"
#include "config.h"
#include "drivers/adc.h"


void readSharpSensors(char *results)
{
	int i, value;
	for(i = 0; i<2; i++)
	{
		value = ADCRead(i+5);
		if(value > SHARP_SENS_THRES)
		{
			results[i] = 1;
		}
		else
		{
			results[i] = 0;
		}

	}
	return;
}



void readLineSensors(char *results)
{
	uint32_t values[4];
	int i;
	for(i=0;i<4;i++)
	{
		values[i] = ADCRead(i);
		#ifdef INVERTED_DOHOYO
		if (values[i] > LINE_SENS_THRES)
		{
			results[i] = 1;
		}
		else
		{
			results[i] = 0;
		}
		#else
		if (values[i] < LINE_SENS_THRES)
		{
			results[i] = 1;
		}
		else
		{
			results[i] = 0;
		}

		#endif
	}
	return;
}
