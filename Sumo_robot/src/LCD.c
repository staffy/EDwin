
/*
 * LCD.c
 *
 *  Created on: 15 okt 2010
 *      Author: staff
 */

#include "LCD.h"

/*
 * Delay for a few ms. Requires SysTick timer to be activated and a global
 * variable msTicks to be defined
 */
void _delay_ms(uint32_t time)
{
	uint32_t startTime = msTicks;
	while( (msTicks - startTime < time) );
}

/*
 * Delay for a few microseconds
 */
void _delay_us( uint32_t u_secs )
{
	int ticks = (SystemCoreClock/1000000 -1) * u_secs;
	int start = SysTick->VAL;	// Sample current value
	int stop;
	if (start - ticks >= 0)
	{
		stop = start - ticks;
		while( SysTick->VAL < start && SysTick->VAL > stop);
		return;
	}
	else
	{
		stop = start + SysTick->LOAD - ticks;
		while( SysTick->VAL > stop || SysTick->VAL < start );
		return;
	}
}

/*
	Used to pulse the E-pin when data should be shifted in.
*/
void _LCD_pulse( void )
{
	_delay_us( 1 );
	LCDPORT_CTRL_E->DATA |= (1 << ENABLE);
	_delay_us( 1 );
	LCDPORT_CTRL_E->DATA ^= (1 << ENABLE);
}

/*
	Internal function used to send 8bit data on a 4bit bus.
*/
void _LCD_sendData( const unsigned char data )
{
	// Clear data bits
	LCDPORT->DATA &= LCD_MASK;


	// Shift in data, first high then low
#if (LCD_OFFSET - 4) >= 0
	LCDPORT->DATA |= ( (data  << (LCD_OFFSET -4)) & ~LCD_MASK );
#else
	LCDPORT->DATA |= ( (data  >> (4 - LCD_OFFSET)) & ~LCD_MASK );
#endif
	_LCD_pulse();
	LCDPORT->DATA &= LCD_MASK; // Clear data bits again
	LCDPORT->DATA |= ( (data << LCD_OFFSET) & ~LCD_MASK );
	_LCD_pulse();

	// Wait for instruction to execute
	_delay_us( 40 );
}

/*
	Used to send commands to the LCD.
*/
void LCD_sendCmd( unsigned char cmd )
{
	// Clear RS
	LCDPORT_CTRL_RS->DATA &= ~( 1 << RS );
	_LCD_sendData( cmd );
}

/*
	Used to send a single char to the LCD.
*/
void LCD_sendChar( unsigned char character )
{
	// Set RS
	LCDPORT_CTRL_RS->DATA |= ( 1 << RS );
	_LCD_sendData( character );
}

/*
	Used to send a string to the LCD.
	The string MUST end with a '\n' character.
*/
void LCD_sendStr( char * text )
{
	unsigned char i;
	for(i = 0; text[i] != '\0' ; i++ )
	{
		LCD_sendChar( text[i] );
	}
}

/*
	Sets the address to the row/column specified in the parameters
	Will only work on a 2 row, 16 column Display
*/
void LCD_addr( unsigned char row, unsigned char column )
{
	LCD_sendCmd( (( row<<6 ) & 0x70) | (column & 0x0F) | 0x80 );
}

/*
	Clears the display, special function needed for this because
	this instruction takes longer than the others.
*/
void LCD_clear()
{
	LCD_sendCmd( 0x01 );
	_delay_ms( 2 );
}

/*
	Display/Cursor home. Special function needed for this because
	this instruction takes longer than the others.
*/
void LCD_home()
{
	LCD_sendCmd( 0x02 );
	_delay_ms( 2 );
}

/*
	Initialize the LCD using proper delays and commands.
*/
void LCD_init( void )
{

	// Set pins as outputs
	LCDPORT->DIR |= (~LCD_MASK & 0xFFF);
	LCDPORT_CTRL_RS->DIR |= (1<<RS);
	LCDPORT_CTRL_E->DIR |= (1<<ENABLE);

	// Initial delay
	_delay_ms( 15 );

	// Initial instuctions
	unsigned char i;
	for (i = 0; i < 3; i++ )
	{
		LCDPORT->DATA &= LCD_MASK ; //Set used pins to zero
		LCDPORT_CTRL_RS->DATA &= ~(1<<RS);

		LCDPORT->DATA |= 0x03 << LCD_OFFSET;	//And set up the command
		_LCD_pulse();

		_delay_ms( 5 );
	}

	// Set 4bit mode
	LCDPORT->DATA &= LCD_MASK;
	LCDPORT->DATA |= 0x02<<LCD_OFFSET;
	_LCD_pulse();

	// Set 2-row display
	LCD_sendCmd( 0x28 );

	// Display off
	LCD_sendCmd( 0x08 );

	// Clear display
	LCD_clear();

	// Set incrementmode, no shift
	LCD_sendCmd( 0x06 );

	// Turn LCD on and set cursor to home
	LCD_sendCmd( 0x0C );
	LCD_home();
}

void SysTick_Handler(void)
{
	msTicks++;
}


