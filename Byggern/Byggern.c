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
#include "SPI.h"
#include "MCP2515.h"
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
	printf("start på program \n");
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


	calibrate();
	OLED_Reset();
	OLED_NameScreen();
	
			
	//CAN_message myMessage;				//test message
	printf("Start på program\n");
	CAN_message in;						//Receiver generated message
	
    
	
	while(1)
    {
		OLED_menu();
		// MENY STUKTUR
				//if(read_knappJoy() == 1)
				//{
					switch(p)
					{
						case 2:
						{
							Game_over = 0;
							OLED_Reset();
							OLED_Home();
							OLED_print("PING-PONG", 8);
							OLED_goto(0, 105);
							OLED_print(&Name, 8);
							_delay_ms(200);
							score = 0;
							oldscore = -1;
							whileplaying(score);

							while (!Game_over)
							{
								CAN_read2(&in);
								_delay_ms(10);
								if (can_flag > 5)
								{
									if (in.id == 25){
										score = in.data[0];
										whileplaying(score);
										if (in.data[1] > 0){
											Game_over = 1;
											death_sfx();
											OLED_Game_Over(score);
											break;
										} 
									}
									Ping_Pong();				// HER SENDES DET EN MELDING
									can_flag = 0;
								}
							}
						}
						break;
						
						case 4  :
						{
							//printf("Highscore");
							OLED_highscore();
							_delay_ms(200);
						}
						break;
						
						case 6:
						{
							OLED_animation();
						}
						break;
						
						default :
						break;
					}
				//}

	



	}
}	

// ISR for CAN timer
ISR(TIMER1_COMPA_vect)
{	
	// Enable sending of joystick data
	can_flag++;
}
