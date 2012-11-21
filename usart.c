#include <avr/io.h>
#include <inttypes.h>
#include "usart.h"

//UBRR_VALUE is defined as F_CPU/(16*baud) - 1 = 8000000/(16*38400) - 1
#define UBRR_VALUE 12 

//void USARTInit(uint16_t ubrr_value)
void USARTInit()
{
   // Set Baud rate
   UBRR = UBRR_VALUE;

   /* Set Frame Format
    * Asynchronous mode
    * No Parity
    * 1 StopBit
    * char size 8
    */

   UCSRC=(1<<URSEL)|(3<<UCSZ0);

   // Enable The receiver and transmitter and interrupts
   UCSRB=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
}

char USARTReadChar()
{
   // busy wait for data
   // while(!(UCSRA & (1<<RXC)));
   return UDR;
}