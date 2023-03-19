/*
 * Application.c
 *
 * Created: 1/29/2023 5:00:12 PM
 *  Author: Karim Nasr
 */ 

// include.h (lower layers)
#include "application.h"

// driver global variables

// function definitions
uint8_t normalMode(void)
{
	static uint8_t firstTimeFlag = 1;	//Raise a flag when the normal mode is started for the very first time in the application.
	if (firstTimeFlag)
	{
		timer0_init_normalMode(4, 166);	//Initialize and start timer0 in normal mode using 256 prescaler and an initial value of 166
		fn_Interface3.led_on(carLeds, carGRN); //Turn on Car Green Led
		firstTimeFlag = 0;	//Lower flag
	}
	return 1;	//Error state = No error / Function OK
}

uint8_t pedMode(void)
{
	pedMode_active = 1;		//Raise a flag when pedestrian mode is active
	//Lower flags (used during pedestrian mode is active)
	pressedAtState0 = 0;	
	pressedAtState1 = 0;
	pressedAtState2 = 0;
	endOfStates = 0;
	switch(state)
	{
		case 0:
			fn_Interface3.led_on(pedLeds, pedRED); //Turn on Ped Red Led
			pressedAtState0 = 1;	//Raise a flag when the crosswalk button is pressed while the normal mode is in state 0
			break;
		case 1:
			fn_Interface3.led_on(pedLeds, pedYLW); //Turn on Ped Yellow Led
			pressedAtState1 = 1;	//Raise a flag when the crosswalk button is pressed while the normal mode is in state 1
			break;
		case 2:
			fn_Interface3.led_on(pedLeds, pedGRN); //Turn on Ped Green Led
			pressedAtState2 = 1;	//Raise a flag when the crosswalk button is pressed while the normal mode is in state 2
			resetOverFlowOrder = 1;	//Raise a flag to order the timer to reset and start over
			break;
		case 3:
			state = 1;	//trigger state 1
			fn_Interface3.led_on(pedLeds, pedYLW); //Turn on Ped Yellow Led
			pressedAtState1 = 1;	//Raise a flag when the crosswalk button is pressed while the normal mode is in state 1
			break;
	}
	return 1;	//Error state = No error / Function OK
}

void start_application(void)
{
	while (1)
	{
		normalMode();	//Loop the normal mode
	}
}
