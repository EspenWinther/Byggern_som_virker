#include <stdlib.h>
#include <avr/io.h>
#include "SRAM_test.h"
#include <stdio.h>



void SRAM_init(void) {
	//Enable the external memory interface/4 bits address
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
	
}

int SRAM_write(unsigned int address, unsigned int data) 
	{
	//Start address for the SRAM
	volatile char *ext_ram = (char *) 0x1800;

	//Write address on SRAM
	ext_ram[address] = data;
	
	return 0;
	}

unsigned int SRAM_read(unsigned int address) 
	{
	//Start address for the SRAM
	volatile char *ext_ram = (char *) 0x1800;
	
	//Read address from SRAM
	return ext_ram[address];
	}