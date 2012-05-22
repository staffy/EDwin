/*
 * drive.h
 *
 *  Created on: 13 mar 2012
 *      Author: Rickard
 */

#ifndef DRIVE_H_
#define DRIVE_H_

// Includes
#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif
#include "gpio.h"
#include "../config.h"

// Pin definitions
#define LEFT_DIR_PORT	0
#define LEFT_DIR_PIN 	6
#define RIGHT_DIR_PORT 	1
#define RIGHT_DIR_PIN 	5


// Global variables
volatile uint16_t TimerCount;

// Functions
void initDrive(void);
void set_speed_left(int percent);
void set_speed_right(int percent);
void setDrive(int speed, int turn);

#endif /* DRIVE_H_ */
