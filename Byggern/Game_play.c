/*
 * CFile1.c
 *
 * Created: 06.11.2017 20:28:04
 *  Author: runarol
 */ 
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "CAN.h"
#include "ADC_test.h"
#include "Joystick.h"
#include <stdio.h>

CAN_message oldMessage;
CAN_message myMessage;		

void Ping_Pong()							// Ping-Pong playing routine
{	
	myMessage.id = 3;						// CAN ID for control data
	myMessage.length = 7;					// Data length
	myMessage.data[0]=ADC_read(0)+100;		// Joystick x
	myMessage.data[1]=ADC_read(1)+100;		// Joystick y
	myMessage.data[2]=ADC_read(2)+100;		// Slider 1
	myMessage.data[3]=ADC_read(3)+100;		// Slider 2
	myMessage.data[4]=read_knappJoy();		// Joystick button
	myMessage.data[5]=read_knappLeft();		// Button left
	myMessage.data[6]=read_knappRight();	// Button right
	for (int i=0; i<7; i++){				// Loop through the data length
											// Try to not overflow the CAN bus
		if (myMessage.data[i] != oldMessage.data[i]){
			CAN_send(&myMessage);			// Send data only if something has changed
			_delay_ms(10);
			break;							// Send only once
		}
	}
	oldMessage = myMessage;					// Save for later
}
