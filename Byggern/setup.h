#ifndef _SETUP_H_
#define _SETUP_H_

#define set_bit(reg, bit) (reg |= (1 << bit))
#define clear_bit(reg, bit) (reg &= ~(1 << bit))
#define test_bit(reg, bit) (reg & (1 << bit))

#define FOSC 4915200UL
//#define F_CPU FOSC

#endif