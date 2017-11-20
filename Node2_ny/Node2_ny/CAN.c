
#include <avr/io.h>
#include "setup.h"
//#define F_CPU FOSC
#include "CAN.h"
#include "MCP2515.h"
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

unsigned char rxflag = 0;									// Interrupt flag variable


void CAN_init()
{
	MCP_init();
	MCP_bitmod(MCP_RXB0CTRL, 0xF0, 0x60);					// Receive Buffer Masks OFF, 0b01100000
	MCP_bitmod(MCP_CANINTE, 0x0F, MCP_RX_INT);				// Sets interrupt receive-register 
	MCP_bitmod(MCP_CANCTRL,MODE_MASK,MODE_NORMAL);			// Setting MCP to loop-back mode MODE_MASK
	_delay_us(10);
	//uint8_t status = MCP_status();
}

void CAN_send(CAN_message * msg)
{


	if (Can_trans_compl())									// Check registers are available 
	{
		_delay_ms(10);
		MCP_write(MCP_TXB0SIDH, msg->id >> 3);				// Write id to id handling register (standard identifier High)
		MCP_write(MCP_TXB0SIDL, msg->id << 5);				// Write id to Id handling register (3-3, standard identifier Low)
		MCP_write(TXB0DLC, (msg->length));					// Write length to length handling register (3-7)
		for(unsigned char i=0; i<msg->length;i++)
		{
			MCP_write(TXB0D0+i,msg->data[i]);				// Write data to the data handling register (3-8). iterate through TXBnDm (n.m =1,2,3...)
		}


		MCP_request();										// Request to send written message MCP_RTS_ALL
	}
	else													// If message is not sent
	{
		printf("Sendte ikke\n");							// Print this
	}
}


int Can_trans_compl()							// sjekker om TX buffer er ferdig med transmission (TXREQ = 0)
{
	if (test_bit(MCP_read(MCP_TXB0CTRL),3))						// Check status-register value against bit 3
	{
		return 0;
	}	
	else
	{
		return 1;
	}
}

void CAN_Int_Reset()						// Resets CAN
{ 
	MCP_bitmod(MCP_CANINTF, 0x01, 0);		// Clearing flag
	rxflag = 1;
}

void CAN_read2(CAN_message * msg)														// Reads a CAN message
{
	if (MCP_read(MCP_CANINTF) & MCP_RX0IF){ // rxflag == 1
		_delay_ms(10);
		//int error = MCP_read(MCP_EFLG);
		msg->id = (MCP_read(MCP_RXB0SIDH) << 3) | (MCP_read(MCP_RXB0SIDL) >> 5);		// Sets MSG ID = to what it reads on the registers											
		msg->length = MCP_read(MCP_RXB0DLC);											// Length is set to what is read on the register
		if(msg->length > 8)
		{
			msg->length = 8;	
		}																				
		for (int i = 0; i< msg->length; i++)
		{
			msg->data[i] = MCP_read(MCP_RXB0D0+i);										// Data is sett to what is read on registers
		}
		//rxflag = 0;																	// Clear intrupt flag. For later
		MCP_bitmod(MCP_EFLG, 0xFF, 0);
		MCP_bitmod(MCP_CANINTF, 0xFF, 0);												// clear the interrupt flag, so the receiver buffer registry can be overwritten
	}
}