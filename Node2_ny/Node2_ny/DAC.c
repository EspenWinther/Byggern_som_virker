#include <avr/io.h>
#include "setup.h"
//#define F_CPU FOSC
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "TWI_Master.h"
#include "DAC.h"


void DAC_init()
{
	TWI_Master_Initialise();

	DDRD |= (PD0<<1) | (PD1<<1);
	//PORTD |= (PD0<<1) | (PD1<<1);
	sei();
}

void DAC_send(unsigned char adr, unsigned char nr, unsigned char value)
{
	unsigned char * msg = malloc(3*sizeof(char));
	msg[0] = adr;					// 7 MSB bit address and 1 LSB chip read (0) byte 
	msg[1] = nr;						// Adress for DAC 0-3, DAC0 = 0
	//printf("Nr: %x\n",msg[1]);
	msg[2] = value;						// Value to put on the chosen DAC
	_delay_us(50);
	TWI_Start_Transceiver_With_Data(msg, 3);
	_delay_us(50);
	free (msg);
}

void DAC_reset(unsigned char adr)
{
	unsigned char * msg = malloc(2*sizeof(char));
	msg[0] = (adr << 1);			// 7 MSB bit address and 1 LSB read (0) byte
	msg[1] = 0b00010000;				// Reset command
	TWI_Start_Transceiver_With_Data(msg, 2);

	free (msg);
}

