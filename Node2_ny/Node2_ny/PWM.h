#include <avr/io.h>
#include <stdio.h>

#ifndef PWM_H_
#define PWM_H_



//#define CLK8 0b010
//#define period_ms (20.0)
//#define duty_cycle_ms (20.0/100.0)
//#define pulse_width_min (0.9/1000.0)
//#define pulse_width_neutral (1.5/1000.0)
//#define pulse_width_max (2.1/1000.0)
//#define clock_scaler CLK8
//#define clock_scaler_val 8

void pwm_init();
//void pwm_width(float poswidth_ms);
uint8_t pwm_set_angle(uint8_t angle,uint8_t mode);

#endif /* PWM_H_ */