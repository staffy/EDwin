/*
 * sharp_sensor.h
 *
 *  Created on: 16 apr 2012
 *      Author: Rickard
 */

#ifndef SHARP_SENSOR_H_
#define SHARP_SENSOR_H_
/*
 * Sensorer på pin:
 * P1.3		AD4 JTAG
 * P1.4		AD5
 * P1.10	AD6
 * P1.11	AD7
 */
// Includes
#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif

#include <stdlib.h>
#include "gpio.h"
#include "adc.h"
#include "drive.h"

// User defines
#define antal 10
#define threshold 260
// Global variables

// Functions
void sharpInit();
uint32_t sharpRead();
uint32_t sharpReadChannel(uint8_t channel);
uint32_t sharpReadMean();
//uint32_t sharpReadFilt();
//uint32_t compare(const void * a, const void * b);

#endif /* SHARP_SENSOR_H_ */
