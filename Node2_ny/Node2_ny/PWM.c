#include "pwm.h"
#include "setup.h"
//#define F_CPU FOSC
#include <util/delay.h>
unsigned int input_range;
unsigned int output_range;
int input_joystick_start;
int input_joystick_end;
uint8_t input_slider_start;
uint8_t input_slider_end;
uint8_t input_joystick_range;
uint8_t input_slider_range;
int output_start;
int output_end;


	//Clear OC1A (channel A) on compare match, use fast PWM, ICR1 used as TOP, prescaler (clk/64)
	//Mode 14 ref arduino s.145
 void pwm_init(){
	TCCR3A |= (1 << WGM31)|(1 << COM3A1);
	TCCR3A &= ~(1 << WGM30)|(1 << COM3A0);
	TCCR3B |= (1 << WGM32)|(1 << WGM33)|(1 << CS31)|(1 << CS30);
	TCCR3B &= ~(1 << CS32);
	//
	ICR3 = 5000;			// TOP value for the timer, 20 ms
	set_bit(DDRE,PE3);		// Sets the PORT 3 as OC3A PWM output port
	OCR3A = 375;			// Compare value for timer, 1-2 ms
	
		input_joystick_start  = 0; // this sets input_joystick_start to 0
		input_joystick_end    = 200;
		input_slider_start    = 0;
		input_slider_end      = 200;
		output_start          = 250;
		output_end            = 500;
		input_joystick_range  = input_joystick_end - input_joystick_start;
		input_slider_range    = input_slider_end - input_slider_start;
		output_range          = output_end - output_start;
 }



uint8_t pwm_set_angle(uint8_t angle, uint8_t mode){
	//printf("Angle: %i\n", angle);
	switch(mode)
	{
		case 1: //Using joystick
		{
			if(angle >= input_joystick_start && angle <= input_joystick_end){
				OCR3A = (angle-input_joystick_start)*output_range / input_joystick_range + output_start;
				return 0;
			}
			break;
		}
		
		case 2: //Using slider
		{
			if(angle >= input_slider_start && angle <= input_slider_end){
				OCR3A = (angle-input_slider_start)*output_range / input_slider_range + output_start;
				return 0;
			}
			break;
		}
	}
	
	return 1;
}