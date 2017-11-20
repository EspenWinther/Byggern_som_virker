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

#define IR_receive PL2 //Port F nr 0

void IR_init()
{
	//using PF0 as receive port, Pull-up on
	clear_bit(DDRL, IR_receive);
	set_bit(PORTL, IR_receive);
	}

int IR_read()
{
	int read = test_bit(PINL, PL2);
		if (read > 0){
			return 1;
		}else{
			return 0;
		}

}
