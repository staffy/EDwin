/*
 * LCD_lib.h
 *
 *  	Created on: 15 okt 2010
 *      Authors: Staffan Sjöqvist, Niklas Norin
 *
 *
 *      Description:
 *      Driver for an HD44780 LCD for ARM Cortex M3.
 *
 *      Requires SysTick Timer to be set up to 1ms interval, and to increment the global variable "msTicks"
 *		in the interrupt. The GPIO pins must be manually set up if they have other functions as default.
 *
 *		SysTick initialization:
 *		SysTick_Config( SystemCoreClock/1000 );
 *
 *		SysTick Handler:
 *		void SysTick_Handler(void)
		{
			msTicks++;
		}
 *
 *
 *
 *
 */



#ifndef LCD_H_
#define LCD_H_

#include "LPC13xx.h"
#include "variables.h"

//#define LABPLATTAN

#ifdef LABPLATTAN
// LABPLATTAN
// Ports used for control and data transfer the LCD, pin 0-3 used for data
#define LCDPORT 		LPC_GPIO2		// Data port
#define LCDPORT_CTRL 	LPC_GPIO2	// Control signals

// Port pins
#define RS 		0	// Pin used for Register Select
#define ENABLE 	1	// Pin used for Enable pin

// Offset used for adjusting which bits are used, for example LCD_OFFSET = 4 uses pins 4:7 for data.
#define LCD_OFFSET 6

#endif

#ifndef LABPLATTAN
// MODERKORTET
// Ports used for control and data transfer the LCD, pin 0-3 used for data
#define LCDPORT 		LPC_GPIO2		// Data port
#define LCDPORT_CTRL 	LPC_GPIO0	// Control signals

// Port pins
#define RS 		1	// Pin used for Register Select
#define ENABLE 	3	// Pin used for Enable pin

// Offset used for adjusting which bits are used, for example LCD_OFFSET = 4 uses pins 4:7 for data.
#define LCD_OFFSET 3

#endif
// */





// Creates a bit mask used to not modify bits not used by LCD.
#define LCD_MASK ( ((0xFF0 << LCD_OFFSET) | (0xFFF >> (12-LCD_OFFSET))) & 0xFFF )


// External function prototypes

void LCD_init( void );
void LCD_sendCmd( unsigned char cmd );
void LCD_sendChar( unsigned char character );
void LCD_sendStr( char * text );
void LCD_addr( unsigned char row, unsigned char column );
void LCD_clear();
void LCD_home();

// Internal function prototypes
void _LCD_pulse( void );
void _LCD_sendData( unsigned char data );
void _delay_ms(uint32_t time);
void _delay_us( uint32_t u_secs );

#endif /* LCD_H_ */


