/*
 * led.h
 *
 * Created: 1/19/2023 2:28:59 PM
 *  Author: Karim Nasr
 */ 

#include "../../MCAL/DIO/dio.h"
#include "../../MCAL/Timer/timer.h"

#ifndef LED_H_
#define LED_H_

// all internal driver typedefs
// all driver macros

// all driver function prototypes
uint8_t LED_init(uint8_t ledPort, uint8_t ledPin);
uint8_t LED_on(uint8_t ledPort, uint8_t ledPin);
uint8_t LED_off(uint8_t ledPort, uint8_t ledPin);
uint8_t LED_toggle(uint8_t ledPort, uint8_t ledPin);

#endif /* LED_H_ */