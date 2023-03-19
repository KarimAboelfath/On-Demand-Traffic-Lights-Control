/*
 * Application.h
 *
 * Created: 1/29/2023 5:00:05 PM
 *  Author: Karim Nasr
 */ 

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "../ECUAL/LED/led.h"
#include "../ECUAL/Button/button.h"

// all internal driver typedefs
// all driver macros

// all driver function prototypes
uint8_t normalMode(void);
uint8_t pedMode(void);
void start_application(void);

#endif /* APPLICATION_H_ */