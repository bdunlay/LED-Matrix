/* Name: main.c
 * Author: Brian Dunlay
 * LED Matrix Controller for the ATtiny2313a
 */
 
#include "shift.h"
#include "timer8.h"
#include "timer16.h"
#include "types.h"
#include "frame.h"
#include "usart.h"
#include <avr/interrupt.h>
#include <util/delay.h>

#define REFRESH_CYCLE_COUNT 60 // 60.0961538 hertz
#define SERIAL_TIMEOUT 2000 // time to send byte is ~1666 cycles @ 8MHz, give some leeway for the timeout



int line = 0;

int main()
{
	// set a default image to the display
	char smiley[] = {0x00, 0x04, 0x42, 0x02, 0x02, 0x42, 0x04, 0x00};
	char full[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

	// initialize for shift registers
	initializeShift();

	// set the clock pre-scaler value to 1
	CLKPR = 0x80; 
	CLKPR = 0x00;

	USARTInit();

	// initialize interrupts and timer0
	sei();
	timer8_enable_int();
	timer8_init(REFRESH_CYCLE_COUNT, CLOCK_SCALE_1024);
	timer8_start();

    // initialize interrupts and timer1 for serial line timeout
    timer16_enable_int();
    timer16_init(SERIAL_TIMEOUT, CLOCK_SCALE_1);

	// so we can see what's happening
	setFrame(full);

	// wait for everything to initialize.
	// UART likes to tick a bit (4x) at first sometimes
	_delay_ms(1000);
	
	// reinitialize the starting point to 0
	line = 0;
	
	setFrame(smiley);

	while(1);
}

/* Timer IRQ handler */
ISR(TIMER0_COMPA_vect) {
	print(getFrame());
}

ISR(USART_RX_vect) {
    // if it's receiving the first byte, start the timeout
    if (line == 0)
        timer16_start();
    else if (line == 7)
        timer16_stop(); // stop the timeout if it's the last bit
    else
        timer16_set_count(0); // otherwise reset the countdown
	unsigned char byte = (unsigned char) UDR;
	setFrameLine(byte, line++);
	line = line % 8;
}

ISR(TIMER1_COMPA_vect) {
    timer16_stop();
    line = 0;
}

