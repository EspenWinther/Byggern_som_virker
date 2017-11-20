#include <avr/io.h>
#include "setup.h"
//#define F_CPU FOSC
#include <util/delay.h>
#include "control_driver.h"
#include "DAC.h"
#include <avr/sleep.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define SOLONOIDE PG5 //Port G nr 5

void sol_init()
{
	//using PA1 as solonoide
	set_bit(DDRG, SOLONOIDE);
	//clear_bit(DDRE, SOLONOIDE);
}

void sol_shot(int fire)
{
	if (fire){
		set_bit(PORTG, SOLONOIDE);
		//_delay_ms(200);
	}
	else{
		clear_bit(PORTG, SOLONOIDE);
	}
}
