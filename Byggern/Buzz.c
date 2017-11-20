#include <avr/io.h>
#include "setup.h"
#include <util/delay.h>
#include "Buzz.h"
#include "Joystick.h"



void buzzinit()
{
set_bit(DDRE,PE2);		// Sets the PORT 3 as OC3A PWM output port
OCR1B = 100;


}

#define LED_PORT    PORTE
#define LED_PIN     2
#define LED_off()  LED_PORT&=~_BV(LED_PIN)
#define LED_on() LED_PORT|=_BV(LED_PIN)

void buzz(unsigned int freq, int time)
{
	while (time>0)
	{
	LED_on();
	delayUS(freq);
	LED_off();
	delayUS(freq);
	time--;
	}
}

void death_sfx()
{
	buzz(1915,15);
	buzz(1700,15);
	buzz(1519,15);
	buzz(1450,15);
	buzz(1432,15);
	buzz(1275,15);
	buzz(1136,15);
	buzz(1014,15);
	buzz(1956,20);
}

void Shoot_sfx()
{
	if (read_knappJoy())
	{
		buzz(500,5);
		buzz(250,5);
		buzz(100,5);
	}
}

void delayUS(unsigned int time)
{
	while(time > 0)
	{
		_delay_us(1);
		time--;
	}
}

