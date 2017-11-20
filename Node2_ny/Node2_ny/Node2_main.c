/*
 * GccApplication1.c
 *
 * Created: 23.10.2017 15:19:53
 *  Author: gautevn
 */ 

#include "setup.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "UART.h"
#include "SPI.h"
#include "MCP2515.h"
#include "CAN.h"



int main(void)
{
UartInit();
CAN_init();

	sei();
	
	/*CAN_message h;								//Receiver generated message

	CAN_message myMessage;				//test message
	int ident = 29;
	myMessage.id = ident;
	myMessage.length = 8;
	int n = 3;
	for (int i = 0; i < 8; i++)
	{
		myMessage.data[i] = n;
		n++;
	}
	printf("Start på program\n");
	
    while(1)
    {
		printf("HEIA");
		CAN_send(&myMessage);
		CAN_read2(&h);
		//h.id=h.data[0];
		printf("h id = %d "  ,h.id  );
		printf("h length = %d "  , h.length  );
		printf("h= ");
		if (h.id == ident)
		{
			for (int i =0; i<8; i++)
			{
				printf("%d, ",h.data[i]);
			}
			printf("\n");
		}
		//CAN_send(&h);
    }*/
}