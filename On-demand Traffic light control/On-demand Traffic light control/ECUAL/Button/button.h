/*
 * button.h
 *
 * Created: 1/19/2023 3:10:40 PM
 *  Author: Karim Nasr
 */ 

#include "../../MCAL/DIO/dio.h"
#include "../../MCAL/Interrupts/interrupts.h"

#ifndef BUTTON_H_
#define BUTTON_H_

// all internal driver typedefs
// all driver macros

// all driver function prototypes
uint8_t BUTTON_init(uint8_t buttonPort, uint8_t buttonPin);
uint8_t BUTTON_read(uint8_t buttonPort, uint8_t buttonPin, uint8_t *value);

#endif /* BUTTON_H_ */