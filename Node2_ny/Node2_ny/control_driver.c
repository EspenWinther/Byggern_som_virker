#include <avr/io.h>
#include "setup.h"
//#define F_CPU FOSC
#include <util/delay.h>
#include <avr/sleep.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "control_driver.h"
#include "DAC.h"

#define vel_max 90
#define vel_min -90
#define dt 0.02

#define DAC_address 0b01010000		// 7 bit address for the DAC, 3 LSB should be connected to GND on chip
#define DAC_number 0				// DAC number 0-3

int16_t encoder_value ;
int16_t encoder_max = 10000;
int16_t reference_max = 180;		//Reference max is slighly smaller than max_value to help gain in extremes
int clock_seconds;
uint8_t counter;
volatile uint8_t pid_flag;
float error_sum = 0;
float last_error = 0;
float kp;
float kd;
float ki;
int16_t integrator_max = 150;
extern int CANcounter = 0;
extern int Scorecounter = 0; 


void CD_init()
{
	DAC_init();										// DAC init
	CD_clk_init();									// Init the Score clock
	
	// Port H pins as Outputs
	set_bit(DDRH, RST);
	set_bit(DDRH, OE);
	set_bit(DDRH, EN);
	set_bit(DDRH, DIR);
	set_bit(DDRH, SEL);
		
	// Port K Digital input Port A Output
	DDRK = 0x00;
	clear_bit(MJ1,OE);								// enable encoder						
	CD_encoder_reset();								// reset encoder
	CD_speed(0);									// sett start speed 
	set_bit(MJ1,EN);								// enable motor
	encoder_max = CD_encoder_max();					// Find encoder max
	
	clock_seconds = 0;								
	counter = 0;
	//CD_set_ref_pos(125);							// sett startpos to middle
	error_sum = 0;
	
	
}

void CD_clk_init()
{
		OCR1A = 5000;

		//Enable CTC mode
		TCCR1A |= (1 << COM1A0);

		//Prescale 64
		TCCR1B |= (1 << CS11) | (1 << CS10) | (1 << WGM12);
		
		//Enable compare match A interrupt
		TIMSK1 |= (1 << OCIE1A);
		
}

int16_t CD_read_encoder()
{
	volatile int16_t data;
	clear_bit(MJ1, OE);			// Enable reading encoder
	clear_bit(MJ1, SEL);		// Choose to read MSB
	_delay_us(20);				// Wait
	
	data |= ((MJ2)<<8);			// Save MSB
	
	set_bit(MJ1, SEL);			// Choose to read LSB
	_delay_us(20);				// Wait
	
	data |= ((MJ2)<<0);			// Save LSB
	_delay_us(5);				// Wait
	
	encoder_value += data;		// Append data to encoder value
	CD_encoder_reset();			// Reset the encoder to avoid overflow
	set_bit(MJ1, OE);			// Disable reading encoder
	return encoder_value;		// Return the updated encoder value
}

void CD_direc(unsigned char direc)
{		//Set the correct value to the motor box pin according to direction
	if (direc == 1)
	{
		set_bit(MJ1, DIR);
	}
	if (direc == 0)
	{
		clear_bit(MJ1, DIR);
	}
}


void CD_speed(int value)
{		// Send motor speed value to DAC
	DAC_send(DAC_address, DAC_number, value);
}

void CD_velocity(int vel)
{
	if (vel > 1){			// Check sign of velocity
		CD_direc(1);		// Set direction according to sign
	}
	else{
		CD_direc(0);
	}
	CD_speed(abs(vel));		// Run motor
}

void CD_pid_gain(float p,float i,float d)
{
	kp = p/1000;
	ki = i/1000;
	kd = d/1000;
}


void CD_PID(int16_t reference_value)
 {
	 	// Use PID when playing, pid_flag set by timer at 50 Hz
		 if (pid_flag){
			 
		 	int16_t encoder_value = CD_read_encoder();		// Read current encoder value
			 // Error value is summed up 
		 	float error = reference_value-(encoder_value*(float)reference_max/encoder_max);
			 
			error_sum += (dt*counter)*error;		// Integral error based on time passed
		 	
			if (error_sum < -integrator_max){		// Limit integral error
			 	error_sum = -integrator_max;
		 	}
			 
			else if (error_sum > integrator_max){	// Limit integral error
				error_sum = integrator_max;
			}
			
			float dErr = (error - last_error) / (dt*counter);	// Derivative error based on size of change
				// Output is summed up, cast to float to avoid overflow and allow decimals
			float output = -(kp * error + ki * error_sum + kd * dErr);
			last_error = error;						// Save the error for later

			if(output>vel_max){						// Limit output
				output= vel_max;
			}
			if(output<vel_min){						// Limit output
				output= vel_min;
			} 

		 	CD_velocity((int) output);				// Adjust position
			_delay_ms(5);
		}
		pid_flag = 0;								// Reset counter and flag
		counter = 0;
 }
 
 ISR(TIMER1_COMPA_vect)		
 {
	//Running on 50Hz
	counter++;			// Counter for PID computations
	CANcounter++;		// Counter for CAN transmission
	Scorecounter++;		// Counter for scores in gameplay
	pid_flag = 1;		// Flag for enable PID controller
 }
 
 
 
 void CD_encoder_reset()
 {		// Reset the encoder
	 clear_bit(MJ1, RST);
	 _delay_us(200);
	 set_bit(MJ1, RST);
 }
 
int16_t CD_encoder_max()
 {
	 printf("Finding encoder max\n");
	 
	 CD_velocity(80);		// 80 is maximum motor speed that the thread does not slip on the pulleys
	 _delay_ms(2000);		// Run for n milliseconds
	 CD_velocity(0);		// Stop
	 _delay_ms(200);		// Wait
	 CD_encoder_reset();	// Reset encoder to 0
	 _delay_ms(10);			// Wait
	 CD_velocity(-80);		// Run backwards, 
	 _delay_ms(3000);		// Run for n milliseconds
	 CD_velocity(0);		// Stop
	 _delay_ms(100);		// Wait
	 int16_t encoder = CD_read_encoder();	// Read the maksimum value from the encoder
	 _delay_ms(10);			// Wait
	 printf("Encoder MAX: %i\n", encoder);
	 CD_velocity(80);		// Run towards center
	 _delay_ms(500);		// Run for n milliseconds
	 CD_velocity(0);		// Stop
	 return (encoder);		// return maksimum encoder value
 }
 

 
 