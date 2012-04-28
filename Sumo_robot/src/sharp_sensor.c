/*
 * sharp_sensor.c
 *
 *  Created on: 16 apr 2012
 *      Author: Rickard
 */
#include "sharp_sensor.h"

void sharpInit()
{
	  LPC_IOCON->PIO1_4 &= ~0x8F; //Nollställer
	  LPC_IOCON->PIO1_4 |= 0x01; /* ADC IN5 */
	  LPC_IOCON->PIO1_10 &= ~0x8F; //Nollställer
	  LPC_IOCON->PIO1_10 |= 0x01; /* ADC IN6 */
	  LPC_IOCON->PIO1_11 &= ~0x8F; //Nollställer
	  LPC_IOCON->PIO1_11 |= 0x01; /* ADC IN7 */
	  GPIOSetDir( 1, 4, 0 ); //AD5 input
	  GPIOSetDir( 1, 10, 0 );//AD6 input
	  GPIOSetDir( 1, 11, 0 );//AD7 input
	  LPC_IOCON->PIO1_4   = (1<<6)|(1<<0);      //select AD5
	  LPC_IOCON->PIO1_10  = (1<<6)|(1<<0);      //select AD6
	  LPC_IOCON->PIO1_11  = (1<<6)|(1<<0);      //select AD7
}
uint32_t sharpRead()
{
	uint32_t i = 0;
	uint32_t sharpValue;
	for ( i = 0; i < 3; i++ )
	{
		sharpValue = ADCRead(5);

		if( sharpValue >= 300 )
		{
			return 5; //i+5
		}
	}
	return 0;
}

uint32_t sharpReadMean()
{
	uint16_t i, j;
	uint32_t sens_mean, sens_0;

	for ( i = 0; i < 3; i++ )
	{

		sens_mean=0;
		sens_0 = ADCRead(i+5);
		for(j=0;j<antal;j++)
		{
			sens_mean=sens_mean + ADCRead(i+5);
		}
		sens_mean=sens_mean/antal;  // Medlvärde för att få bort störningar
		if( sens_mean > threshold)
		{
			return i+5;   // set the LED on
		}
	}
	return 0;
}
/*
uint32_t sharpReadFilt()
{
	uint32_t i = 0;
	uint32_t j = 0;
	uint32_t Value;
	uint32_t sharpValue[4];
	uint32_t filteredValues[3];
	for ( i = 0; i < 3; i++ )
	{
		for ( j = 0; j < 4; j++ )
		{
			sharpValue[j] = ADCRead( 5 );
			Value = ADCRead( 5 );
			//_delay_ms(5);
		}
		for(j=0; j<3; j++)
		{
			filteredValues[j]=sharpValue[j+1];
		}
		qsort(filteredValues, 3, sizeof(uint32_t), compare);
		if( filteredValues[1] >= 220 )
		{
			return filteredValues[1]; //i+5
		}
	}
	return 0;
}*/

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
/*
uint32_t compare (const void * a, const void * b)
{
  return ( *(uint32_t*)a - *(uint32_t*)b );
}*/
