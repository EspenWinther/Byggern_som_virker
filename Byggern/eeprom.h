/*
 * IncFile1.h
 *
 * Created: 06.11.2017 20:34:07
 *  Author: runarol
 */ 
#include "CAN.h"

#ifndef Game_play_H_
#define Game_play_H_

void write_eeprom(unsigned int uiAddress, unsigned char ucData);
unsigned char EEPROM_read(unsigned int uiAddress);



#endif /* INCFILE1_H_ */