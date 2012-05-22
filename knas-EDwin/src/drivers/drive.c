/*
 * drive.c
 *
 *  Created on: 13 mar 2012
 *  Author: Rickard
 */
//PWM 1.6 (RXD), 1.7 (TXD)
#include "drive.h"
#include "gpio.h"

/*
 * Initializes timer32B0 as PWM
 */
void initDrive(void)
{
	//TimerCount = (1/TargetFrequency)/(prescaler/ProcessorClockFrequency) - 1;
	TimerCount = 2399;
	LPC_GPIO0->DIR |= (1 << 6);				// Port0 bit6 OUTPUT, Left_dir_pin
	LPC_GPIO0->DIR |= (1 << 10);			// Port0 bit10 OUTPUT, Left_enable
	LPC_GPIO1->DIR |= (1 << 5);        		// Port1 bit5 OUTPUT, Right_dir_pin
	LPC_GPIO1->DIR |= (1 << 8);				// Port1 bit8 OUTPUT, Right_Enable
	set_speed_right(0);
	set_speed_left(0);
	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 9);	// Enable clock to timer 0, CT32B0
	//LPC_IOCON->PIO1_9 |= (1 << 0);        // set bit 0 to connect pin to CT16B1_MAT0
	//LPC_IOCON->PIO1_9 |= (1 << 1);        	// set bit 1 to connect pin 10 to CT16B1_MAT1
	LPC_IOCON->PIO1_6 &= ~0x1F;			// - remove bits 0,1 & 2 and pull resistors
	LPC_IOCON->PIO1_6 |= 0x02;			//CT32B0_MAT0
	LPC_IOCON->PIO1_7 &= ~0x1F;     	// - remove bits 0,1 & 2 and pull resistors
	LPC_IOCON->PIO1_7 |= 0x02;        	/* CT32B0_MAT1 */
	LPC_TMR32B0->MCR |= (1 << 10);			// Reset TC counter when it reaches Match Register 3 value
	LPC_TMR32B0->PR = 0;					// Prescale 347
	LPC_TMR32B0->MR0 = TimerCount;          // TMR32B0 Match register 0
	LPC_TMR32B0->MR1 = TimerCount;          // TMR32B0 Match register 1
	LPC_TMR32B0->MR3 = TimerCount;//4096;            	// Cycle length 4096 (= 50.6574Hz) - Match register 3
	LPC_TMR32B0->PWMC |= 3;					// Timer 1 MAT0 and MAT1 is PWM

	LPC_TMR32B0->TCR = 1;    				// enable timer 1
	set_speed_right(0);
	set_speed_left(0);
	return;
}


void set_speed_left(int percent)
{
	LPC_TMR32B0->MR0 = TimerCount-percent*(TimerCount-0.05*TimerCount)/100;
	return;
}
/*
 * Sets the speed by changing the duty cycle of the PWM-signal
 *
 * Parameter: percent = sets the speed. Range [-100,100] -100 is full reverse, 100 is full forward
 */
void set_speed_right(int percent)		// percent1 = 0 => neutral, percent1 < 0 => reverse, percent1 > 0 => forward ; range: -100 to 100
{
	LPC_TMR32B0->MR1 = TimerCount-percent*(TimerCount-0.05*TimerCount)/100;
	return;
}

void setDrive(int speed, int turn)
{
	// positive turn means turning right, positive speed means driving forward
	int left, right;
	left = speed-turn;
	right = speed+turn;

	// Set motor speeds
	// Left motor
	if( left >= 0)
	{
		GPIOSetValue( LEFT_DIR_PORT, LEFT_DIR_PIN, INVERT_LEFT_MOTOR );
		if(left > MAX_MOTOR_SPEED) // Speed limit :-)
		{
			left = MAX_MOTOR_SPEED;
		}
		set_speed_left(left);
	}
	else
	{
		GPIOSetValue( LEFT_DIR_PORT, LEFT_DIR_PIN, (INVERT_LEFT_MOTOR ^ 0x01) );
		left = -left;
		if(left > MAX_MOTOR_SPEED) // Speed limit :-)
		{
			left = MAX_MOTOR_SPEED;
		}
		set_speed_left(left);
	}

	// Right motor
	if( right >= 0)
	{
		GPIOSetValue( RIGHT_DIR_PORT, RIGHT_DIR_PIN, INVERT_RIGHT_MOTOR );
		if(right > MAX_MOTOR_SPEED) // Speed limit :-)
		{
			right = MAX_MOTOR_SPEED;
		}
		set_speed_right(right);
	}
	else
	{
		right = -right;
		GPIOSetValue( RIGHT_DIR_PORT, RIGHT_DIR_PIN, (INVERT_RIGHT_MOTOR ^ 0x01) );
		if(right > MAX_MOTOR_SPEED) // Speed limit :-)
		{
			right = MAX_MOTOR_SPEED;
		}
		set_speed_right(right);
	}
}
