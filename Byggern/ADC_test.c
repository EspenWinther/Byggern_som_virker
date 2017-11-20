#include <avr/io.h>
#include "ADC_test.h"
#include <util/delay.h>



int ADC_read(char channel)
{
	_delay_us(50);
	volatile char *ext_adc = (char *) 0x1400; // Start address for the AAM
	int retrieved_value = 0;

	*ext_adc = 0b0100 + channel;
	_delay_us (50);
	// remapping
	retrieved_value = *ext_adc;
	int val;
	val = (((float)(retrieved_value-128)/127)*100);
	val = (int) val;
	
	// deadzone	
	if((-10 < val) & (10 > val)){
		val=0;
	}
	return val;
}



void ADC_init()
{	
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
}

