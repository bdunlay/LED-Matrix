/*
 * main.c
 *
 * Created: 5/15/2012 1:21:57 AM
 *  Author: Brian
 *
 * Note: added these flags to compiler: -U lfuse:w:0x64:m -U hfuse:w:0xdd:m -U efuse:w:0xff:m
 * Set a define as F_CPU = 1000000 (1 Mhz... save power... full speed is not necessary)
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

typedef unsigned char byte;

// PORT D
#define D_SER	PORTD2// serial data
#define D_OE	PORTD3// output enable 
#define D_SRCLK	PORTD4// clock in data
#define D_SRCLR	PORTD5// clear serial registers
#define D_RCLK	PORTD6// move serial bits to registers for output

// PORT B
#define S_SER	PORTB0
#define S_OE	PORTB1
#define S_SRCLK	PORTB2
#define S_SRCLR	PORTB3
#define S_RCLK	PORTB4

#define DISPLAY_WIDTH	8

#define PRESCALE	8
#define TIMER_CT	(F_CPU/PRESCALE)/1000 - 1 // 1 mS count

enum shiftRegisters{
	DATA,
	SELECT
};


void init_io() {
	
	DDRD = 0x3F;
	DDRD = 0x00;

	DDRB = 0xFF;
	DDRB = 0x00;
	
}

void init_timer() {
	TCCR1B |= (1 << WGM12);
	OCR1A = TIMER_CT;
	TCCR1B |= (1 << CS11); // Start timer at Fcpu/8
}	
byte currentData[8];

void writeShift(byte data, int width, int t) {

	int i ;
	
	for (i = 0; i < width; i++) {
		
		if (t == DATA) {
			PORTD &= ~(1<<D_SRCLK); // set serial clock low
			PORTD |= (((data&(0x01<<i))>>i)<<D_SER); // put data on serial pin
			PORTD |= (1<<D_SRCLK); //pull serial register clk high
			PORTD &= ~(((data&(0x01<<i))>>i) << D_SER ); // put data pin low
		}
		else if (t == SELECT) {
			PORTB &= ~(1<<S_SRCLK); // set serial clock low
			PORTB |= (((data&(0x01<<i))>>i)<<S_SER); // put data on serial pin
			PORTB |= (1<<S_SRCLK); // put serial register clk high
			PORTB &= ~(((data&(0x01<<i))>>i) << S_SER ); // put data pin low
		}
	}

	// output data 	
	if (t == DATA) {
		PORTD |= (1 << D_RCLK);
	} else if (t == SELECT) {
		PORTB |= (1 << S_RCLK);
	}

}



// this will be on an interrupt timer
void refresh() {
	int i;
	int select = 0x01;
	for (i = 0; i < 8; i++) {
		
		// write a row of 8 bits		
		writeShift(currentData[i], DISPLAY_WIDTH, DATA);
		
		// select that row
		writeShift(select, 1, SELECT);
		
		// perpetuate the 
		if (select) select = 0x00;
		
		_delay_ms(1);
	}
	
	writeShift(select, 1, SELECT);
}

ISR(TIMER1_COMPA_vect) {
	refresh();
}

void printMatrix(byte data[]) {
	int i = 0;
	for (i = 0; i < 8; i++) {
		currentData[i] = data[i];
	}	
}

int main(void) {
	
	init_io();
	init_timer();
	
    while(1) {

		// read uart
		// translate to 64 bits 
		// printMatrix(byte[])

    }
}