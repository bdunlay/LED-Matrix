/* Name: main.c
 * Author: Brian Dunlay
 * LED Matrix Controller for the ATtiny2313a
 */
 
#include "shift.h"
#include "timer8.h"
#include "types.h"
#include "frame.h"
//#include "usart.h"
#include <avr/interrupt.h>
#include <util/delay.h>

#define REFRESH_CYCLE_COUNT 130 // 60.0961538 hertz







int main()
{
	// set a default image to the display
	char smiley[] = {0x00, 0x04, 0x42, 0x02, 0x02, 0x42, 0x04, 0x00};
	char flatFace[] = {0x00, 0x02, 0x42, 0x02, 0x02, 0x42, 0x02, 0x00};
	char sadFace[] = {0x00, 0x01, 0x42, 0x02, 0x02, 0x42, 0x01, 0x00};

	char h[] = 	{0x00, 0x00, 0xFF, 0xAA, 0xAA, 0x0F, 0x00, 0x00};
	char e[] = 	{0x00, 0x00, 0x0E, 0x15, 0x15, 0x09, 0x00, 0x00};
	char ll[] = 	{0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00};
    char o[] = 	{0x00, 0x00, 0x0E, 0x11, 0x11, 0x0E, 0x00, 0x00};
    char test[] = {0,0,0,0,0,0,0,0};



//	setFrame(h);

	// initialize for shift registers
	initializeShift();

	// initialize interrupts and timer0
	sei();
	timer8_enable_int();
	timer8_init(REFRESH_CYCLE_COUNT, CLOCK_SCALE_1024);
	timer8_start();
	//USARTInit();
	
	setFrame(smiley);

	while(1)
	{

	// setFrame(smiley);
	// _delay_ms(10);
	// setFrame(flatFace);
	// _delay_ms(1);
	// setFrame(sadFace);
	// _delay_ms(10);
	// setFrame(flatFace);
	// _delay_ms(1);

	//	int i, j;
	//	for (i = 0; i < 8; i++) {
	//		for (j = 1; j < 256; j *= 2) {
	//			test[i] ^= j;
	//			setFrame(test);
	//			_delay_ms(1);
	//		}
	//	}
	}
}

/* Timer IRQ handler */
ISR(TIMER0_COMPA_vect) {
	print(getFrame());
}

/*ISR(USART0_vect) {
	char btye = USARTReadChar();
}*/