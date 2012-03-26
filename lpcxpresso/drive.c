/*
 * drive.c
 *
 *  Created on: 13 mar 2012
 *      Author: Rickard
 */

#include "drive.h"

/*
 * Initializes timer16B1 as PWM
 */
void initDrive(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 8);	// Enable clock to timer 1, CT16B1
	//LPC_IOCON->PIO1_9 |= (1 << 0);        	// set bit 0 to connect pin to CT16B1_MAT0
	LPC_IOCON->PIO1_10 |= (1 << 1);        	// set bit 1 to connect pin 10 to CT16B1_MAT1
	LPC_TMR16B1->MCR |= (1 << 10);			// Reset TC counter when it reaches Match Register 3 value
	LPC_TMR16B1->PR = 347;					// Prescale 347
	LPC_TMR16B1->MR0 = 4096 - 224;          // TMR16B1 Match register 0
	LPC_TMR16B1->MR1 = 4096 - 361;          // TMR16B1 Match register 1
	LPC_TMR16B1->MR3 = 4096;            	// Cycle length 4096 (= 50.6574Hz) - Match register 3
	LPC_TMR16B1->PWMC |= 3;					// Timer 1 MAT0 and MAT1 is PWM
	//LPC_GPIO1->DIR |= (1 << 9);        		// Port1 bit9 OUTPUT
	LPC_GPIO1->DIR |= (1 << 10);        	// Port1 bit10 OUTPUT
	LPC_GPIO0->DIR |= (1 << 4);				// Port0 bit4 OUTPUT, Right_dir_pin
	LPC_GPIO0->DIR |= (1 << 5);				// Port0 bit5 OUTPUT, Left_dir_pin
	LPC_TMR16B1->TCR = 1;    				// enable timer 1
	set_speed(50);
	return;
}

/*
 * Sets the steering angle by changing the duty cycle of the PWM-signal
 *
 * Parameter: percent = sets the steering angle. Range [0,100] 0 is full right, 100 is full left
 */
/*
void set_steering(percent)		// 0 percent = full right, 100 percent = full left ; range: 0 to 100
{
	LPC_TMR16B1->MR0 = 4096 - (224 + 226*percent/100);
	return;
}
*/

/*
 * Sets the speed by changing the duty cycle of the PWM-signal
 *
 * Parameter: percent = sets the speed. Range [-100,100] -100 is full reverse, 100 is full forward
 */
void set_speed(int percent)		// percent1 = 0 => neutral, percent1 < 0 => reverse, percent1 > 0 => forward ; range: -100 to 100
{
	LPC_TMR16B1->MR1 = 4096 - (300 + 132*percent/100);
	speed=percent;
	return;
}

void set_direction(int left, int right)
{
	GPIOSetValue( dir_port, Right_dir_pin, right );
	GPIOSetValue( dir_port, Left_dir_pin, left );
}

void set_movement(int movement)
{
	switch(movement)
	{
	case 0:		//Forward
		set_direction(0,0);
		break;
	case 1:		//Reverse
		set_direction(1,1);
		break;
	case 2:		//Turn Right
		set_direction(0,1);
		break;
	case 3:		//Turn Left
		set_direction(1,0);
		break;
	default:
		break;
	}
}
