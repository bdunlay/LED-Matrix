/*
 * timer.c
 *
 * Created: 5/16/2012 11:09:53 AM
 *  Author: Brian
 */ 

#include <avr/io.h>
#include "timer.h"

void init_timer() {
	TCCR1B |= (1 << WGM12);
	OCR1A = TIMER_CT;
	TCCR1B |= (1 << CS11); // Start timer at Fcpu/8
}