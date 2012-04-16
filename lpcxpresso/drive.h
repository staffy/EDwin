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
#define left_dir_port 0
#define left_dir 6
#define left_enable 10
#define right_dir_port 0
#define right_dir 5
#define right_enable 8
#define TargetFrequency 30000
#define ProcessorClockFrequency 72000000
#define prescaler 1

// Global variables
volatile uint32_t speed_left;
volatile uint32_t speed_right;
volatile uint16_t TimerCount;

// Functions
void initDrive(void);
void set_speed(int percent);
void set_direction(int left, int right);
void set_movement(int movement);
void enable_engines(void);
void disable_engines(void);

#endif /* DRIVE_H_ */
