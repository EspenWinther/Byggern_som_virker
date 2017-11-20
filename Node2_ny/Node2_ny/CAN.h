#ifndef CAN_h_
#define CAN_h_
#include <avr/io.h>

unsigned char rxflag;
typedef struct
{
	uint8_t id;
	uint8_t length;
	uint8_t data[8];
} CAN_message;


void CAN_init();
void CAN_send(CAN_message * msg);
int Can_trans_compl();

void CAN_Int_Reset();

//unsigned char CAN_read(); 
void CAN_read2(CAN_message * msg);

#endif