/*
 * utilities.h
 *
 * Created: 1/19/2023 1:03:22 PM
 *  Author: Karim Nasr
 */ 

#ifndef UTILITIES_H_
#define UTILITIES_H_

//Macros for setting, clearing and toggling bit/s
#define SET_BIT(reg, bit) (reg |= (1 << bit))	 //example: SET_BIT(x, 5);
#define SET_BITS(reg, bits) (reg |= (bits))		 //example: SET_BITS(x, (1 << 2) | (1 << 5));
#define CLEAR_BIT(reg, bit) (reg &= ~(1 << bit)) //example: CLEAR_BIT(x, 5);
#define CLEAR_BITS(reg, bits) (reg &= ~(bits))	 //example: CLEAR_BITS(x, (1 << 2) | (1 << 5));
#define TOGGLE_BIT(reg, bit) (reg ^= (1 << bit)) //example: TOGGLE_BIT(x, 5);

#endif /* UTILITIES_H_ */