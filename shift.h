/*
 * shift.h
 *
 * Created: 5/16/2012 10:54:44 AM
 *  Author: Brian
 */ 


#ifndef SHIFT_H_
#define SHIFT_H_

#include "common.h"

// PORT D
#define D_SER	PORTD2// serial data
#define D_OE	PORTD3// output enable
#define D_SRCLK	PORTD4// clock in data
#define D_SRCLR	PORTD5// clear serial registers
#define D_RCLK	PORTD6// move serial bits to registers for output

// PORT B
#define S_SER	PORTB0
#define S_OE	PORTB1
#define S_SRCLK	PORTB2
#define S_SRCLR	PORTB3
#define S_RCLK	PORTB4

void writeShift(byte, int, int);


#endif /* SHIFT_H_ */