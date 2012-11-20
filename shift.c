/* Name: shift.c
 * Author: Brian Dunlay
 * Shift functions for LED Matrix for the ATtiny2313a
 * Some code borrowed / reworked from http://bildr.org/2011/02/74hc595/
 */

#ifndef SHIFT_H
#define SHIFT_H
#endif

#include "shift.h"
#include <avr/io.h>
#include <util/delay.h>

/*
 * function:	initializeShift
 * description:	Sets the pin directions on the mcu to out and sets their value to low
 * Calls resetShiftRegisters() to reset the attached shift registers
 */
void initializeShift() 
{
	// direction = out
	DDRB = 0xFF;
	// clear all pins 
	PORTB = 0x00; /* set pins to low */
	// reset shift registers
	resetShiftRegisters();
}

/*
 * function:	resetShiftRegisters
 * description:	Since the reset pins are initialized to 0, this pulls them high to enable
 * their correct operation (~SRRST needs to be high to work!)
 */
void resetShiftRegisters()
{

	PORTB |= (1 << PB1);
	PORTB |= (1 << PB5);
}

/*
 * function:	print
 * paramaters:	char[] of length 8
 * description:	each byte of this array corresponds to a column of the bitmap to be
 * printed on the display
 */
void print(char frame[]) 
{
	int i;
	int columnBit;

	for (i = 0; i < 8; i++)	
	{
		if (i == 0) 
		{
			columnBit = 0x01;
		}
		else
		{
			columnBit = 0x00;
		}

		// select column
		shiftBit(PB6, PB4, PB7, ~columnBit);
		// print column
		shiftByte(PB2, PB0, PB3, frame[i]);
		// clear column
		shiftByte(PB2, PB0, PB3, 0x00);
	 }

}

/*
 * function:	shiftBit
 * paramaters:	int SRCLK_Pin, int RCLK_Pin, int SER_Pin, unsigned long data
 * description:	shifts the register attached to the pins specified in the parameters
 * a single bit (as passed in the data parameter)
 */
void shiftBit(int SRCLK_Pin, int RCLK_Pin, int SER_Pin, unsigned long data)
{
	PORTB &= ~(1 << RCLK_Pin); 				// Set the register-clock pin low

	PORTB &= ~(1 << SRCLK_Pin); 			// Set the serial-clock pin low
	//_delay_ms(100);
	PORTB |= (data << SER_Pin); 	// Go through each bit of data and output it
	//_delay_ms(100);
	PORTB |= (1 << SRCLK_Pin); 			// Set the serial-clock pin high
	//_delay_ms(100);
	PORTB &= ~(data << SER_Pin);	// Set the datapin low again
	//_delay_ms(100);

	PORTB |= (1 << RCLK_Pin);				// Set the register-clock pin high to update the output of the shift-register

}

/*
 * function:	shiftByte
 * paramaters:	int SRCLK_Pin, int RCLK_Pin, int SER_Pin, unsigned long data
 * description:	loads a full byte of (the parameter) data into the shift register
 * attached to the pins specified in the parameters
 */
void shiftByte(int SRCLK_Pin, int RCLK_Pin, int SER_Pin, unsigned long data)
{
	PORTB &= ~(1 << RCLK_Pin); 				// Set the register-clock pin low

	int i;
	for (i = 0; i < (8); i++)
	{	// Now we are entering the loop to shift out 8+ bits

		PORTB &= ~(1 << SRCLK_Pin); 			// Set the serial-clock pin low
		//_delay_ms(100);
		PORTB |= (((data&(0x01<<i))>>i) << SER_Pin ); 	// Go through each bit of data and output it
		//_delay_ms(100);
		PORTB |= (1 << SRCLK_Pin); 			// Set the serial-clock pin high
		//_delay_ms(100);
		PORTB &= ~(((data&(0x01<<i))>>i) << SER_Pin );	// Set the datapin low again
		//_delay_ms(100);
	}

	PORTB |= (1 << RCLK_Pin);				// Set the register-clock pin high to update the output of the shift-register
}


