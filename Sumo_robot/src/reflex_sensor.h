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

/* FRONT
 * 0---1
 * |   |
 * |   |
 * |   |
 * 2---3
 *  BACK
 */

#define REFLEX_1_PORT 0
#define REFLEX_2_PORT 1
#define REFLEX_3_PORT 1
#define REFLEX_4_PORT 1
#define REFLEX_1_BIT 11
#define REFLEX_2_BIT 0
#define REFLEX_3_BIT 1
#define REFLEX_4_BIT 2

// Global variables
volatile uint32_t reflexValue[REFLEX_NUM];
// Functions
void reflexAnalogInit();
uint32_t reflexReadAnalog();
uint32_t readReflexChannel(uint32_t channel);
void reflexDigitalInit();
uint32_t reflexReadDigital();

//void PIOINT2_IRQHandler(void);
//void PIOINT3_IRQHandler(void);

#endif /* REFLEX_SENSOR_H_ */
