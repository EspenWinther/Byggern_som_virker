// MCP driver file: Espen 08.10.17
#include "setup.h"
//#define F_CPU FOSC
#include "MCP2515.h"
#include "SPI.h"
#include "CAN.h"
#include <avr/io.h>
#include <util/delay.h>


void MCP_init()
{
	// Makes sure registers are clean and MCP in control mode
	SPI_MasterInit();
	MCP_reset();
	_delay_us(10);
}



void MCP_bitmod(unsigned char reg, unsigned char mask, unsigned char data)
{
	spi_chipselect(1);					// Chip select
	_delay_us(1);
	SPI_tranciever(MCP_BITMOD);			// send command "I want to modify bit"
	_delay_us(1);
	SPI_tranciever(reg);				// In what register do you want to operate
	_delay_us(1);
	SPI_tranciever(mask);				// What bit mask do you want to change
	_delay_us(1);
	SPI_tranciever(data);				// What to you want to change to
	_delay_us(1);
	spi_chipselect(0);						// chip de-select
	
}
// Note that bitmod will change multiple bits unless one specifies which bit address to change. f.ex: bit = DLC3 & DLC2
// This will only change these two, but to use the function this way DLC3 and DCL2 must be defined first

unsigned int MCP_read(unsigned int address)
{
	unsigned int result;
	spi_chipselect(1);				// Selects can controller
	_delay_us(1);
	SPI_tranciever(MCP_READ);		// Send command "I want to read MCP"
	_delay_us(1);
	SPI_tranciever(address);		// Address we want to read
	_delay_us(1);
	result = SPI_tranciever(0xFF);	// Save What we read in result
	_delay_us(1);
	spi_chipselect(0);				// De-selects can controller
	//printf("Result %i\n",result);
	return result;					// Return what we read
}

void MCP_write(unsigned int address, unsigned int data)
{
	spi_chipselect(1);	
	_delay_us(1);				
	SPI_tranciever(MCP_WRITE);		// Send command "I want to write"
	_delay_us(1);
	SPI_tranciever(address);		// Where we want to write to
	_delay_us(1);
	SPI_tranciever(data);			// What we want to write
	_delay_us(1);
	spi_chipselect(0);
}

void MCP_reset()
{
	spi_chipselect(1);	
	SPI_tranciever(MCP_RESET);		// Send command "I want to reset MCP"
	spi_chipselect(0);
}

void MCP_request()
{
	spi_chipselect(1);
	SPI_tranciever(MCP_RTS_ALL);	// Send command "Request to send for all ports" (TX0, TX1 and TX2)
	spi_chipselect(0);
}

unsigned int MCP_status()
{
	spi_chipselect(1);
	//SPI_tranciever(0x90);
	SPI_tranciever(MCP_READ_STATUS);									// Send command "I want to read status"
	unsigned char value  = 	SPI_tranciever(0xFF);						// Save returned value for SPI_ tranciever
	spi_chipselect(0);	
	return value;														// Return saved variabel 
}

