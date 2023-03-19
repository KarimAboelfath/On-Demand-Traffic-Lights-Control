/*
 * timer.c
 *
 * Created: 1/19/2023 6:59:51 PM
 *  Author: Karim Nasr
 */ 

// include.h (lower layers)
#include "timer.h"

// driver global variables

// function definitions
uint8_t timer0_init_normalMode(uint8_t prescaler, uint8_t initialValue)
{
	if (prescaler < 0 || prescaler > 7)
	{
		return 0; //Function Error - wrong input
	}
	else
	{
		//Set the timer0 mode to Normal mode
		//TCCR0 &= ~((1 << WGM01) | (1 << WGM00));
		//TCCR0 &= ~((1 << 3) | (1 << 6));
		CLEAR_BITS(TCCR0, (1 << 3) | (1 << 6));
		
		//Clear the 3-least significant bits in TCCR0
		//TCCR0 &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
		//TCCR0 &= ~((1 << 2) | (1 << 1) | (1 << 0));
		CLEAR_BITS(TCCR0, (1 << 2) | (1 << 1) | (1 << 0));
		
		TCNT0 = initialValue;	//Set initial value
		
		// Enable overflow interrupt
		//TIMSK0 |= (1 << TOIE0);
		//TIMSK |= (1 << 0);
		SET_BIT(TIMSK, 0);
		
		SET_BIT(SREG, 7);	//Enable global interrupts
		TCCR0 |= prescaler;	//Set prescaler and start timer0 (start counting)
		return 1;	//Function OK
	}
}