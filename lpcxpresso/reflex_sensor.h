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
 * P0.11
 * P1.0
 * P1.1
 * P1.2
 */
// Includes
#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif
#include "gpio.h"
#include "drive.h"
// User defines

// Functions
void initReflex(void);
void PIOINT2_IRQHandler(void);
void PIOINT3_IRQHandler(void);

#endif /* REFLEX_SENSOR_H_ */
