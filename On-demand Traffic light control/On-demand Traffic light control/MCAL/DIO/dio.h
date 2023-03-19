/*
 * dio.h
 *
 * Created: 1/19/2023 12:31:40 PM
 *  Author: Karim Nasr
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "../../Utilities/registers.h"

// all internal driver typedefs
// all driver macros

//Port Defines
#define PORT_A 'A'
#define PORT_B 'B'
#define PORT_C 'C'
#define PORT_D 'D'

//Direction Defines
#define IN 0
#define OUT 1

//Value Defines
#define LOW 0
#define HIGH 1

// all driver function prototypes
uint8_t DIO_init  (uint8_t portNumber, uint8_t pinNumber, uint8_t direction); // Initialize DIO direction
uint8_t DIO_write (uint8_t portNumber, uint8_t pinNumber, uint8_t value); // Write data to DIO
uint8_t DIO_toggle(uint8_t portNumber, uint8_t pinNumber); // Toggle DIO
uint8_t DIO_read  (uint8_t portNumber, uint8_t pinNumber, uint8_t *value); // Read DIO

#endif /* DIO_H_ */