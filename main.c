/* Name: main.c
 * Author: Brian Dunlay
 * LED Matrix Controller for the ATtiny2313a
 */
 
#include <avr/io.h>
#include "shift.h"

int main()
{
	// initialize for shift registers
	initializeShift();

	// smiley face
	char frame[] = {0x00, 0x04, 0x42, 0x02, 0x02, 0x42, 0x04, 0x00};

	while(1)
	{
		print(frame);
	}
}

