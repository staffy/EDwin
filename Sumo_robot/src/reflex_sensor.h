/*
 * reflex_sensor.h
 *
 *  Created on: 15 mar 2012
 *      Author: Rickard
 */

#ifndef REFLEX_SENSOR_H_
#define REFLEX_SENSOR_H_
/*
 * Sensorer på pin:
 * P0.11	AD0
 * P1.0		AD1
 * P1.1		AD2
 * P1.2		AD3
 */
// Includes
#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif
#include "gpio.h"
#include "adc.h"
#include "drive.h"
// User defines
#define REFLEX_NUM 4

// Global variables
volatile uint32_t reflexValue[REFLEX_NUM];
// Functions
uint16_t reflexRead();
//void PIOINT2_IRQHandler(void);
//void PIOINT3_IRQHandler(void);

#endif /* REFLEX_SENSOR_H_ */
