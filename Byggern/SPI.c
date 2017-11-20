#include <avr/io.h>


void SPI_MasterInit(void)
{
	/* Set MOSI, SS and SCK output, all others input */
	DDRB &= ~(1<<PB6);
	DDRB |= (1<<PB5)|(1<<PB7)|(1<<PB4);
	PORTB |= (1<<PB4);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);//&~(1<<DORD);
	
	// Enable Global Interrupts
	// sei(); vil heller få interup externt, ikke fra spi
}

unsigned char SPI_tranciever(unsigned char data)
{

	/* Start transmission */

	SPDR = data;
	/* Wait for transmission complete */
	while (!(SPSR & (1<<SPIF)));

	//Return received data
	return SPDR;
}

//void testSPI(){
		//uint8_t dummy=	0xFF;//MCP_read(0x0E);
		//MCP_write(0x0F,0x40);
		//dummy=	MCP_read(0x0F);
		//_delay_ms(1000);
//}