#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

//#include <avr/io.h>

#define RST PH6
#define OE PH5
#define EN PH4
#define DIR PH1
#define SEL PH3
#define MJ2 PINK
#define MJ1 PORTH

void CD_init();
//void CD_set_ref_pos(unsigned char pos);
void CD_clk_init();
int16_t CD_read_encoder();
void CD_direc(unsigned char direc);
void CD_speed(int value);
void CD_velocity(int vel);
void CD_pid_gain(float p,float i,float d);
void CD_PID(int reference_value);
void CD_encoder_reset();
int16_t CD_encoder_max();
int CANcounter;
int Scorecounter;

#endif