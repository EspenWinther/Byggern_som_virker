#include "setup.h"
//#define F_CPU FOSC
#include <avr/io.h>
#include <stdio.h>
#include "UART.h"

#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void UartInit(void){
	UBRR0L = (uint8_t)(MYUBRR);
	UBRR0H = (uint8_t)((MYUBRR) >> 8);

	// USART Control and Status
	UCSR0B  |=  (1<<RXEN0)      // receive enable
			|   (1<<TXEN0);     // transmit enable

	UCSR0C  |=	(1 << USBS1)	// 2 stop bites
			|	(3<<UCSZ00);    // char size to 8
	
	fdevopen(&USART_Transmit, &USART_Receive);
}

unsigned char USART_Receive(void)
	{
	//Wait for data to be received
	while ( !(UCSR0A & (1<<RXC0)) );
	
	//Get and return received data from buffer
	return UDR0;
	}

void USART_Transmit( unsigned char data )
	{
	//Wait for empty transmit buffer
	while ( !( UCSR0A & (1<<UDRE0)) );
	
	//Put data into buffer, sends the data
	UDR0 = data;
	}

