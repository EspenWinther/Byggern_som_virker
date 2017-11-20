#ifndef __Bluetooth_spi_H
#define __Bluetooth_spi_H

#define BS_Reset 0x00
#define BS_Read 0x00
#define BS_Write 0x00
#define BS_RTS 0x00
#define BS_ReadStatus 0x00
#define BS_Bitmod 0x00

void BlueSPI_init();
void BlueSPI_write(unsigned int address, unsigned int data);
unsigned int BlueSPI_read(unsigned int address);
void BlueSPI_bitmod(unsigned char reg, unsigned char mask, unsigned char data);
void BlueSPI_reset();
void BlueSPI_request();
unsigned int BlueSPI_status();

#endif
