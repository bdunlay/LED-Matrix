/* Name: frame.c
 * Author: Brian Dunlay
 * Frame functions for LED Matrix for the ATtiny2313a
 */
 
#include "frame.h"

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

void setFrameLine(char data, int lineNumber){

	frame[lineNumber] = data;

}