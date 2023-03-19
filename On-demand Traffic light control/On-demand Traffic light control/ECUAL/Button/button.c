/*
 * buttonm.c
 *
 * Created: 1/19/2023 3:10:49 PM
 *  Author: Karim Nasr
 */ 

// include.h (lower layers)
#include "button.h"

// driver global variables

// function definitions
uint8_t BUTTON_init(uint8_t buttonPort, uint8_t buttonPin) //Set the Button as an Input device
{
	DIO_init(buttonPort, buttonPin, IN); // Button pin set to Input
	return 1;	//Function OK
}
uint8_t BUTTON_read(uint8_t buttonPort, uint8_t buttonPin, uint8_t *value)	//Check the button status (pressed or not) //Read the value on the button pin (1 or 0).
{
	DIO_read(buttonPort, buttonPin, value); // Read button pin input
	return 1;	//Function OK
}
