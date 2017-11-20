#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
//#include <avr/stdint.h>
#include <stdio.h>
#include "setup.h"
#include "Joystick.h"
#include "ADC_test.h"
#include "OLED.h"
#include <util/delay.h>


void joy_init()
{
	
}

void calibrate(){
	OLED_Reset();
	OLED_Home();
	OLED_goto(0, 10);
	OLED_print("Vennligst roter", 8);
	OLED_goto(2,10);
	OLED_print("Joystick", 8);
	OLED_goto(4,10);
	OLED_print("Deretter:", 8);
	OLED_goto(6,10);
	OLED_print("Trykk Joyknapp", 8);
	
	int x_akse=ADC_read(0);
	int y_akse=ADC_read(1);

	int x_akse_min=100;
	int x_akse_max=-100;
	int y_akse_min=100;
	int y_akse_max=-100;
	int x_center = ADC_read(0);
	int y_center = ADC_read(1);
	printf("Rotate the joystick ");
	// Wating for user and printing none calibrated values of the joystick
	while(((-10 > x_akse) | (x_akse > +10)) & ((-10 > y_akse) | (y_akse > +10))){
		_delay_ms(1000);
		printf("Rotate joystick and press butten when done\n");
		 x_akse=ADC_read(0);
		 y_akse=ADC_read(1);
	}
	while(!read_knappJoy()){
		_delay_ms(100);
		x_akse=ADC_read(0);
		y_akse=ADC_read(1);
		if(x_akse_min>x_akse){x_akse_min=x_akse;}
		if(x_akse_max<x_akse){x_akse_max=x_akse;}
		if(y_akse_min>y_akse){y_akse_min=y_akse;}
		if(y_akse_max<y_akse){y_akse_max=y_akse;}
		//printf ("xMin: %i xMaks: %i yMin: %i yMaks: %i \n", x_akse_min,x_akse_max,y_akse_min,y_akse_max);
	}
	int calibrated [] = {x_akse_min,x_akse_max,y_akse_min,y_akse_max};
	printf ("Kalibrerte verdier: \n xMin: %i xMaks: %i yMin: %i yMaks: %i \n xAVG: %i yAVG: %i \n", calibrated[0],calibrated[1],calibrated[2],calibrated[3], x_center, y_center);
}


int8_t read_y()
{
return ADC_read(0);
}

int8_t read_x()
{
return ADC_read(1);
}

char read_knappJoy()
{
	if (1 > (PINB & (1<<PINB2))){
		return 1;
	}
	return 0;
}

// Omgjør verdiene til bool 
char read_knappLeft()
{	
	if (test_bit(PINB, PINB1)){
		return 1;
	}
	return 0;
}


char read_knappRight()
{
	if(test_bit(PINB, PINB0)){
		return 1;
	}
	return 0;		
}