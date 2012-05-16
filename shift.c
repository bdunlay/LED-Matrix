/*
 * shift.c
 *
 * Created: 5/16/2012 10:56:48 AM
 *  Author: Brian
 */ 

#include <avr/io.h>
#include "shift.h"

void writeShift(byte data, int width, int t) {

	int i ;
	
	for (i = 0; i < width; i++) {
		
		if (t == DATA) {
			PORTD &= ~(1<<D_SRCLK); // set serial clock low
			PORTD |= (((data&(0x01<<i))>>i)<<D_SER); // put data on serial pin
			PORTD |= (1<<D_SRCLK); //pull serial register clk high
			PORTD &= ~(((data&(0x01<<i))>>i) << D_SER ); // put data pin low
		}
		else if (t == SELECT) {
			PORTB &= ~(1<<S_SRCLK); // set serial clock low
			PORTB |= (((data&(0x01<<i))>>i)<<S_SER); // put data on serial pin
			PORTB |= (1<<S_SRCLK); // put serial register clk high
			PORTB &= ~(((data&(0x01<<i))>>i) << S_SER ); // put data pin low
		}
	}

	// output data
	if (t == DATA) {
		PORTD |= (1 << D_RCLK);
	} else if (t == SELECT) {
		PORTB |= (1 << S_RCLK);
	}

}
