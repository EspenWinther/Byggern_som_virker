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

void Ping_Pong()
{	
	myMessage.id = 3;
	myMessage.length = 7;
	myMessage.data[0]=ADC_read(0)+100;
	myMessage.data[1]=ADC_read(1)+100;
	myMessage.data[2]=ADC_read(2)+100;
	myMessage.data[3]=ADC_read(3)+100;
	myMessage.data[4]=read_knappJoy();
	myMessage.data[5]=read_knappLeft();
	myMessage.data[6]=read_knappRight();
	for (int i=0; i<7; i++){
		//Try to not overflow the CAN bus
		if (myMessage.data[i] != oldMessage.data[i]){
			CAN_send(&myMessage);
			_delay_ms(10);
			break;
		}
	}
	oldMessage = myMessage;
}
