/* Name: main.c
 * Author: Brian Dunlay
 * LED Matrix Controller for the ATtiny2313a
 */
 
#include "shift.h"
#include "timer8.h"
#include "types.h"
#include "frame.h"
#include <avr/interrupt.h>

#define REFRESH_CYCLE_COUNT 65 // 60.0961538 hertz

int main()
{

	char smiley[] = {0x00, 0x04, 0x42, 0x02, 0x02, 0x42, 0x04, 0x00};
	setFrame(smiley);

	// initialize for shift registers
	initializeShift();

	// initialize interrupts and timer0
    sei();
    timer8_enable_int();
    timer8_init(REFRESH_CYCLE_COUNT, CLOCK_SCALE_256);
    timer8_start();

	while(1);
}

/* Timer IRQ handler */
ISR(TIMER0_COMPA_vect) {
	print(getFrame());
}