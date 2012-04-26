/*
 * drive.c
 *
 *  Created on: 13 mar 2012
 *      Author: Rickard
 */
//PWM 1.6 (RXD), 1.7 (TXD)
#include "drive.h"

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
	disable_engines();
	set_movement(2, 60);
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
	set_speed_right(40);
	set_speed_left(80);
	return;
}

void set_speed(int percent)
{
	set_speed_left(percent);
	set_speed_right(percent);
}

void set_speed_left(int percent)
{
	LPC_TMR32B0->MR0 = TimerCount-percent*(TimerCount-0.05*TimerCount)/100;
	speed_left=percent;
}
/*
 * Sets the speed by changing the duty cycle of the PWM-signal
 *
 * Parameter: percent = sets the speed. Range [-100,100] -100 is full reverse, 100 is full forward
 */
void set_speed_right(int percent)		// percent1 = 0 => neutral, percent1 < 0 => reverse, percent1 > 0 => forward ; range: -100 to 100
{
	LPC_TMR32B0->MR1 = TimerCount-percent*(TimerCount-0.05*TimerCount)/100;
	//LPC_TMR16B1->MR1 = 2399-percent*(2399-20)/100;
	speed_right=percent;
	return;
}

void enable_engines(void)
{
	GPIOSetValue( right_dir_port, right_enable, 1 );
	GPIOSetValue( left_dir_port, left_enable, 1 );
}

void disable_engines(void)
{
	GPIOSetValue( right_dir_port, right_enable, 0 );
	GPIOSetValue( left_dir_port, left_enable, 0 );
}

void set_direction(int left, int right)
{
	GPIOSetValue( right_dir_port, right_dir, right );
	GPIOSetValue( left_dir_port, left_dir, left );
}

void set_movement(int movement, int speed)
{
	switch(movement)
	{
	case 0:		//Forward
		set_direction(0,0);
		set_speed(speed);
		break;
	case 1:		//Reverse
		set_direction(1,1);
		set_speed(speed);
		break;
	case 2:		//Turn Right
		set_direction(0,1);
		set_speed(speed);
		break;
	case 3:		//Turn Left
		set_direction(1,0);
		set_speed(speed);
		break;
	default:
		break;
	}
}
