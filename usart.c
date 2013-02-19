#include <avr/io.h>
#include <inttypes.h>
#include "usart.h"

//UBRR_VALUE is defined as F_CPU/(16*baud) - 1 = 8000000/(16*38400) - 1
#define UBRR_VALUE 12 


//void USARTInit(uint16_t ubrr_value)
void USARTInit()
{
  /* Set baud rate */
  UBRRH = (unsigned char)(UBRR_VALUE>>8);
  UBRRL = (unsigned char)UBRR_VALUE;
  /* Enable receiver and transmitter */
  UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
  /* Set frame format: 8data, 2stop bit */
  UCSRC = (1<<UCSZ1)|(1<<UCSZ0);

   // // Set Baud rate
   // UBRRL |= UBRR_VALUE;

   //  Set Frame Format
   //  * Asynchronous mode
   //  * No Parity
   //  * 1 StopBit
   //  * char size 8
    

   // UCSRC=(1<<UCSZ0)|(1<<UCSZ1);

   // // Enable The receiver and transmitter and interrupts
   //UCSRB=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
}

unsigned char USARTReadChar()
{
   // busy wait for data
   // while(!(UCSRA & (1<<RXC)));
   return (unsigned char) UDR;
}

void USARTSendChar(char* data, int length)
{
   // get pointer to the head of the LL
   // gotta verify all of the pointer logic
   int i;
   for (i = 0; i < length; i++) {

   }
}