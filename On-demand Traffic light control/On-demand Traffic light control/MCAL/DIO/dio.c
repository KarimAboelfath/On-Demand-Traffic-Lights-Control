/*
 * dio.c
 *
 * Created: 1/19/2023 12:32:10 PM
 *  Author: Karim Nasr
 */ 

// include.h (lower layers)
#include "dio.h"
// driver global variables

// function definitions 

uint8_t DIO_init(uint8_t portNumber, uint8_t pinNumber, uint8_t direction) // Initialize DIO direction (Input or Output)
{
	switch(portNumber)
	{
		case PORT_A:
			if(direction == IN)
			{
				CLEAR_BIT(DDRA, pinNumber); // Input
				return 1;	//Function OK
			}
			else if(direction == OUT)
			{
				SET_BIT(DDRA, pinNumber);   // Output
				return 1;	//Function OK
			}
			else 
			{
					return 0;	//Function Error
			}
		break;
		case PORT_B:
		if(direction == IN)
		{
			CLEAR_BIT(DDRB, pinNumber); // Input
			return 1;	//Function OK
		}
		else if(direction == OUT)
		{
			SET_BIT(DDRB, pinNumber);   // Output
			return 1;	//Function OK
		}
		else
		{
			return 0;	//Function Error
		}
		break;
		case PORT_D:
		if(direction == IN)
		{
			CLEAR_BIT(DDRD, pinNumber); // Input
			return 1;	//Function OK
		}
		else if(direction == OUT)
		{
			SET_BIT(DDRD, pinNumber);   // Output
			return 1;	//Function OK
		}
		else
		{
			return 0;	//Function Error
		}
		break;
		default:
		{
			return 1;	//Function OK
		}
	}
}
uint8_t DIO_write(uint8_t portNumber, uint8_t pinNumber, uint8_t value) // Write data to DIO (HIGH or LOW) (1 or 0).
{
	switch(portNumber)
	{
		case PORT_A:
		if(value == LOW)
		{
			CLEAR_BIT(PORTA, pinNumber); // Write 0
			return 1;	//Function OK
		}
		else if(value == HIGH)
		{
			SET_BIT(PORTA, pinNumber);   // Write 1
			return 1;	//Function OK
		}
		else
		{
			return 0;	//Function Error
		}
		break;
		case PORT_B:
		if(value == LOW)
		{
			CLEAR_BIT(PORTB, pinNumber); // Write 0
			return 1;	//Function OK
		}
		else if(value == HIGH)
		{
			SET_BIT(PORTB, pinNumber);   // Write 1
			return 1;	//Function OK
		}
		else
		{
			return 0;	//Function Error
		}
		break;
		default:
		{
			return 0;	//Function Error
		}
	}
}
uint8_t DIO_toggle(uint8_t portNumber, uint8_t pinNumber) // Toggle DIO
{
	switch(portNumber)
	{
		case PORT_A:
		TOGGLE_BIT(PORTA, pinNumber); //Toggle bit
		return 1;	//Function OK
		break;
		case PORT_B:
		TOGGLE_BIT(PORTB, pinNumber); //Toggle bit
		return 1;	//Function OK
		break;
		default:
		return 0;	//Function Error
	}
}
uint8_t DIO_read(uint8_t portNumber, uint8_t pinNumber, uint8_t *value)// Read DIO
{
	switch(portNumber)
	{
		case PORT_B:
		*value = (PINB & (1 << pinNumber)) >> pinNumber;// get state -> read bit
		return 1;	//Function OK
		break;
		case PORT_D:
		*value = (PIND & (1 << pinNumber)) >> pinNumber;// get state -> read bit
		return 1;	//Function OK
		break;
		default:
		return 0;	//Function Error
	}
}