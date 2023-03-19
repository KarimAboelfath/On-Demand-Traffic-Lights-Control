/*
 * led.c
 *
 * Created: 1/19/2023 2:29:07 PM
 *  Author: Karim Nasr
 */ 

// include.h (lower layers)
#include "led.h"

// driver global variables

// function definitions
uint8_t LED_init(uint8_t ledPort, uint8_t ledPin) //Initialize LED as an Output device
{
	DIO_init(ledPort, ledPin, OUT); // LED pin set to Output
	return 1;	//Function OK
}
uint8_t LED_on(uint8_t ledPort, uint8_t ledPin) //Turn LED ON
{
	DIO_write(ledPort, ledPin, HIGH); // Write 1 on led pin
	return 1;	//Function OK
}
uint8_t LED_off(uint8_t ledPort, uint8_t ledPin) //Turn LED OFF
{
	DIO_write(ledPort, ledPin, LOW); // Write 0 on led pin
	return 1;	//Function OK
}
uint8_t LED_toggle(uint8_t ledPort, uint8_t ledPin)	//Toggle LED
{
	DIO_toggle(ledPort, ledPin); // Toggle led
	return 1;	//Function OK
}
