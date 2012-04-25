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
#include "gpio.h"
#include "adc.h"
#include "drive.h"

// User defines

// Global variables

// Functions
uint16_t sharpRead();
uint32_t sharpReadChannel(uint8_t channel);
#endif /* SHARP_SENSOR_H_ */
