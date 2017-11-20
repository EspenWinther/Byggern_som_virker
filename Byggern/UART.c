#include <avr/io.h>
#include "UART.h"
#include "setup.h"
//#define F_CPU FOSC
//#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


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


	
//}
void UartInit(){
	//Set Baud rate 9600
	UBRR0H = (unsigned char)(MYUBRR >> 8);	// Setter de 8 mest signifikante bitene
	UBRR0L = (unsigned char)(MYUBRR);	// Setter de 8 minst signifikante bitene
	// Enable receiver and transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	// 8N2
	UCSR0C = (1<<URSEL0) | (1<<USBS0) | (3<<UCSZ00);
	fdevopen(&USART_Transmit, &USART_Receive);
}