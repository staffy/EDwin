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

// User defines
#define dir_port 0
#define Right_dir_pin 4
#define Left_dir_pin 5
// Global variables
volatile uint32_t speed;

// Functions
void initDrive(void);
void set_speed(int percent);
void set_direction(int left, int right);
void set_movement(int movement);

#endif /* DRIVE_H_ */
