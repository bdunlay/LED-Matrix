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
		
		// write a row of 8 bits
		writeShift(currentData[i], DISPLAY_WIDTH, DATA);
		
		// select that row
		writeShift(select, 1, SELECT);
		
		// move the bit down the shift register
		if (select) select = 0x00;

	}
}

void printd(byte data[]) {
	int i = 0;
	for (i = 0; i < 8; i++) {
		currentData[i] = ~data[i]; // invert so that 0s will sink current
	}
}

void test_display() {
		currentData[0] = 0x24; //0 0 1 0 0 1 0 0
		currentData[1] = 0x24; //0 0 1 0 0 1 0 0
		currentData[2] = 0x24; //0 0 1 0 0 1 0 0
		currentData[3] = 0x24; //0 0 1 0 0 1 0 0
		currentData[4] = 0x24; //0 0 1 0 0 1 0 0
		currentData[5] = 0x81; //1 0 0 0 0 0 0 1
		currentData[6] = 0x42; //0 1 0 0 0 0 1 0
		currentData[7] = 0x3C; //0 0 1 1 1 1 0 0
}