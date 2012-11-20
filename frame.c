/* Name: frame.c
 * Author: Brian Dunlay
 * Frame functions for LED Matrix for the ATtiny2313a
 * Some code borrowed / reworked from http://bildr.org/2011/02/74hc595/
 */
 
#include "frame.h"


//char frame[] = {0x00, 0x04, 0x42, 0x02, 0x02, 0x42, 0x04, 0x00};
char frame[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

char* getFrame() 
{
	return frame;
}

void setFrame(char* data)
{
	int i;
	for (i = 0; i < 8; i++)
	{
		frame[i] = data[i];
	}
}