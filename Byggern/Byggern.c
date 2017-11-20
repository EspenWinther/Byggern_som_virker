/*
 * Byggern.c
 *
 * Created: 04.09.2017 10:24:49
 *  Author: gautevn
 */ 
#include <avr/io.h>
#include "setup.h"
//#define F_CPU FOSC
#include <avr/interrupt.h>
#include <avr/sleep.h>
//#include <avr/stdint.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "UART.h"
//#include "SRAM_test.h"
#include "ADC_test.h"
#include "OLED.h"
#include "Joystick.h"
//#include "fonts.h"
#include "Buzz.h"
//#include "SPI.h"
//#include "MCP2515.h"
#include "CAN.h"
#include "Game_play.h"

volatile char Game_over = 0;
volatile char can_flag = 0;
volatile char score = 0;

int main(void)
{
	
	DDRD  = 0xFF;
	DDRB = 0b00011000;				//Output, input på 0-2
	PORTB = 0b00000100;					//pull-up pin2
	
	UartInit();
	//printf("start på program \n");
	//SRAM_init();
	buzzinit();
	ADC_init();
	init_OLED();
	CAN_init();
	
	//Trigger interrupt with interval of 50hz
	OCR1A = 1536;

	//Enable CTC mode
	set_bit(TCCR1A,COM1A0);

	//Prescale 64
	set_bit(TCCR1B, CS11);
	set_bit(TCCR1B, CS10);
	set_bit(TCCR1B, WGM12);
	
	// Enable interrupt on output compare match timer 1
	set_bit(TIMSK, OCIE1A);
	
	// Enable Global Interrupts
	sei();


	calibrate();						// Calibrate Joystick
	OLED_Reset();						// Clear OLED screen
	OLED_NameScreen();					// Get username
	
			
	printf("Start på program\n");		// Test function
	CAN_message in;						// Receiver generated message
	
    
	
	while(1){
		OLED_menu();					// Main Menu returning p
		switch(p)						// p (current line) is used to check which action to use
		{
			case 2:						// Line 2 is used as Ping-Pong game start
			{
				Game_over = 0;				// No Game Over when starting
				OLED_Reset();				// Clear screen
				OLED_Home();				// Start screen at upper left corner
				OLED_print("PING-PONG", 8);	// Print on screen
				OLED_goto(0, 105);			// Upper right corner
				OLED_print(&Name, 8);		// Pring user name
				_delay_ms(200);				// Wait
				score = 0;					// Reset game score
				oldscore = -1;				// Reset compare score variable
				whileplaying(score);		// Update screen with 0 score value

				while (!Game_over)			// Run until Game Over ( IR is tripped)
				{
					CAN_read2(&in);			// Read CAN bus
					_delay_ms(10);			// Read delay
					if (can_flag > 5){		// Write delay, flag is incremented at 50 Hz in ISR
						if (in.id == 2){			// Only one ID is accepted
							score = in.data[0];		// Game score value is received from node 2
							whileplaying(score);	// Update screen with new score
							if (in.data[1] > 0){		// If Game over variable is set
								Game_over = 1;			// GAME OVER
								death_sfx();			// Play Game Over sound
								OLED_Game_Over(score);	// Go to Game Over screen and plot score
								break;					// Stop
							} 
						}
						Ping_Pong();				// Game play routine
						can_flag = 0;				// Reset flag
					}
				}
			}
			break;
						
			case 4  :						// Highscore screen
			{
				OLED_highscore();
				_delay_ms(200);
			}
			break;
						
			case 6:							// Random button
			{
				OLED_animation();			// Play animation
			}
			break;
						
			default :
			break;
		}
	}
}	

// ISR for CAN timer
ISR(TIMER1_COMPA_vect)				// Timer ISR at 50 Hz
{	
	// Enable sending of joystick data
	can_flag++;
}
