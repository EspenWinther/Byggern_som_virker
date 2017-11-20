/*
 * GccApplication1.c
 *
 * Created: 23.10.2017 15:19:53
 *  Author: gautevn Boi
 */ 

#include "setup.h"
//#define F_CPU FOSC
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "control_driver.h"
#include "UART.h"
#include "SPI.h"
#include "MCP2515.h"
#include "CAN.h"
#include "DAC.h"
#include "pwm.h"
#include "Solenoid.h"
#include "IR_ball.h"


CAN_message out;								//Receiver generated message
CAN_message in;							//Receiver generated message
uint16_t joystick_a = 0;
uint8_t joybtn = 0;
uint8_t slider_a = 0;
char DAC_address = 0b01010000;					// 7 bit address for DAC 

 int main(void)
{
	
	UartInit();								// Initialize the UART
	CAN_init();								// Initialize the CAN bus drivers
	CD_init();								// Initialize the Control Driver
	pwm_init();								// Initialize the Servo
	IR_init();								// Initialize the IR controllers
	sol_init();								// Initialize the Solenoid/plunger
	
	cli();					// Clear Global Interrupts
	sei();					// Enable Global Interrupts
	
	_delay_ms(1);
	
	
	
	volatile uint8_t shotcounter = 0;		// Variable for game play score
	
	
	printf("Start på program\n");		// Error detection
	
    while(1)
    {
		CAN_read2(&in);				// Have to read often enough, stops if the bus is not pulled/emptied. 
		_delay_ms(10);				// Read delay
		
		if (CANcounter > 0){		// Write delay
			
			if (!IR_read()){		// Game over if the IR light is broken
				out.id = 25;
				out.length = 2;
				out.data[1] = 1;		// Game over
				CAN_send(&out);			// Send data to node 1
				shotcounter = 0;		// Reset game score
				CD_PID(100);			// Center plunger
				_delay_ms(1000);		// Wait Game over delay
				out.data[0] = shotcounter;		// Send back the reset score
				out.data[1] = 0;		// Reset Game over
				CAN_send(&out);			// Send data to Node 1 
			}
			
			else if (in.id == 3)		// ONLY accept one ID from node 1.
			{
				joystick_a = -in.data[1]+200;	// 0-200 -> 200-0 --- Value received from joystick in node 1 
				joybtn = in.data[4];			// Value from joybutten in node 1
				slider_a = -in.data[2]+200;		// 0-200 -> 200-0 --- Value received from slider in node 1
				CD_pid_gain(2500,6000,200);		// PID values that work: 2500,6000,200
				pwm_set_angle(joystick_a, 1);	// Use joystick to adjust servo
				CD_PID(slider_a);				// Use slider to adjust position of carriage
				sol_shot(joybtn);				// Use button to shoot the plunger
			}	
			
			
			else if (joybtn){
				//printf("Joy");
				if (Scorecounter > 30){		// Delay in shooting to reduce cheating ;-)
					shotcounter++;			// Increase score
					Scorecounter = 0;		
				}
				out.id = 25;				// ID for score and Game over
				out.length = 2;				
				out.data[0] = shotcounter;	// Send new score value
				//out.data[1] = 0;
				CAN_send(&out);				// Send to node 1
				_delay_ms(100);				// Wait a bit
			}
		CANcounter = 0;						// Reset counter
		_delay_ms(10);
		}
	}
}

ISR(__vector_default){}					// Default Interrupt handler, if no other handler; this does nothing.