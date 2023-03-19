/*
 * timer.h
 *
 * Created: 1/19/2023 6:59:43 PM
 *  Author: Karim Nasr
 */ 

#ifndef TIMER_H_
#define TIMER_H_

#include "../../Utilities/registers.h"

// all internal driver typedefs
// all driver macros

// all driver function prototypes
uint8_t timer0_init_normalMode(uint8_t prescaler, uint8_t initialValue);

#endif /* TIMER_H_ */