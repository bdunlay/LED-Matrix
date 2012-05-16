/*
 * gpio.c
 *
 * Created: 5/16/2012 11:13:21 AM
 *  Author: Brian
 */ 

#include <avr/io.h>
#include "gpio.h"

void init_gpio() {
	DDRD = 0x3F;
	DDRD = 0x00;
	DDRB = 0xFF;
	DDRB = 0x00;
}