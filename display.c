/*
 * display.c
 *
 * Created: 5/16/2012 10:46:12 AM
 *  Author: Brian
 */ 

#include "display.h"

byte currentData[8];

void refresh() {
	int i;
	int select = 0x01;
	
	for (i = 0; i < 8; i++) {
		writeShift(currentData[i], DISPLAY_WIDTH, DATA); // write row of 8 bits
		writeShift(select, 1, SELECT); // select row
		if (select) select = 0x00; // push a 0 behind the select bit
	}
}

void printd(byte data[]) {
	int i = 0;

	for (i = 0; i < 8; i++) {
		currentData[i] = ~data[i]; // invert so that 0s will sink current
	}
}

void test_display() {
	byte smiley[8] = {0x24, 0x24, 0x24, 0x24, 0x24, 0x81, 0x42, 0x3C};
	printd(smiley);
}