/*
 * main.c
 *
 * Created: 5/15/2012 1:21:57 AM
 *  Author: Brian
 *
 * Note: added these flags to compiler: -U lfuse:w:0x64:m -U hfuse:w:0xdd:m -U efuse:w:0xff:m
 * Set a define as F_CPU = 1000000 (1 Mhz... save power... full speed is not necessary)
 */ 


#include <avr/interrupt.h>

#include "shift.h"
#include "display.h"
#include "timer.h"
#include "gpio.h"

// called by interrupt timer every 1ms
ISR(TIMER1_COMPA_vect) {
	refresh();
}

int main(void) {
	
	init_gpio();
	init_timer();
	test_display();
    	
	while(1);

}