/*
 * interrupts.c
 *
 * Created: 1/23/2023 1:03:15 PM
 *  Author: Karim Nasr
 */ 

// include.h (lower layers)
#include "interrupts.h"
#include "../DIO/dio.h"

// driver global variables

// function definitions
uint8_t INT0_externalInterrupt_init_risingEdge(void)
{
	// set INT0 to trigger on rising edge
	//SET_BITS(MCUCR, (1 << ISC00) | (1 << ISC01));
	SET_BITS(MCUCR, (1 << 0) | (1 << 1));
	
	//Enable INT0 external interrupt
	//GICR |= (1<<INT0);
	SET_BIT(GICR, 6);
	
	SET_BIT(SREG, 7); // Enable global interrupts
	return 1;
}
//ISR implementation of INT0 External Interrupt
ISR(INT0_vect)
{
	if (!(pedMode_active || endOfStates))
	{
		fn_Interface4.pedMode_callback();	//Activate Pedestrian Mode if it's not already active nor the endOfStates flag is not raised.
	}
}

//ISR implementation of timer0 overflow
ISR(TIMER0_OVF_vect)
{
	static uint16_t overflow_count = 0; //The Overflow Counter
	overflow_count++;
	static uint8_t pedMode_iterCount = 0; //Iterations count or number of passed states in the current activation of the pedestrian mode.
	
	//if it's the first time for the timer0 overflow ISR to run, set the state to 0.
	static uint8_t initialCallFlag = 1;
	if (initialCallFlag)
	{ 
		initialCallFlag = 0;
		state = 0;
	}
	
	//Blink the yellow lEDs by toggling them after the timer0 counter overflows 50 times
	if ((overflow_count != 0) && (overflow_count % 50 == 0) && (state == 1 || state == 3))
	{
		if (pedMode_active || endOfStates)	//If pedestrian mode is active or the endOfStates flag is raised, synchronize the CAR and the PED yellow LEDS and blink (toggle them)
		{
			//Synchronizing the CAR and PED yellow LEDS in the first iteration.
			static uint8_t yellowSync = 0;
			if(!yellowSync)
			{
				yellowSync = 1;
				fn_Interface2.led_off(carLeds, carYLW); //Turn Off Car Yellow Led
				fn_Interface2.led_off(pedLeds, pedYLW); //Turn Off Ped Yellow Led
			}
			//Toggling the CAR and PED yellow LEDS
			fn_Interface.led_toggle(carLeds, carYLW); //Toggle Car Yellow Led
			fn_Interface.led_toggle(pedLeds, pedYLW); //Toggle Ped Yellow Led
		}
		else //If pedestrian mode is NOT active or the endOfStates flag is Lowered, Blink the CAR's yellow LED only.
		{
			fn_Interface.led_toggle(carLeds, carYLW); //Toggle Car Yellow Led
		}
	}
	
	//Reset the timer (overflow counter), if the crosswalk button is pressed at state 2 in which the CAR's RED LED is on; to give the pedestrians extra 5 seconds to cross.
	if (pressedAtState2 && resetOverFlowOrder)
	{
		overflow_count = 611;
		state = 1;
		resetOverFlowOrder = 0;
	}
	
	//Check if desired number of overflows have occurred
	if (overflow_count == 611) 
	{
		// Reset overflow count
		overflow_count = 0;

		// Take desired action
		switch(state)
		{
			case 0:
				if (pedMode_iterCount == 2)
				{
					pedMode_iterCount = 0;
					fn_Interface2.led_off(pedLeds, pedGRN);	fn_Interface2.led_off(pedLeds, pedYLW);	fn_Interface2.led_off(pedLeds, pedRED);	//Turn Off all PED's LEDs.
				}
				if (pedMode_active)
				{
					fn_Interface2.led_off(carLeds, carGRN); //Turn off Car Green Led
					fn_Interface3.led_on(carLeds, carYLW); //Turn on Yellow Led
					//*******************************************************************************************
					fn_Interface2.led_off(pedLeds, pedRED); //Turn off Ped Red Led
					fn_Interface3.led_on(pedLeds, pedYLW); //Turn on Ped Yellow Led
					//*********************
					pedMode_iterCount++;
					if(pedMode_iterCount == 2)
					{
						pedMode_active = 0;
					}
				}
				else
				{
					fn_Interface2.led_off(carLeds, carGRN); //Turn off Car Green Led
					fn_Interface3.led_on(carLeds, carYLW); //Turn on Yellow Led
					//*******************************************************************************************
					fn_Interface2.led_off(pedLeds, pedRED); //Turn off Ped Red Led
				}
				state++;
				break;
			case 1:
				if (pedMode_iterCount == 2)
				{
					pedMode_iterCount = 0;
					fn_Interface2.led_off(pedLeds, pedGRN);	fn_Interface2.led_off(pedLeds, pedYLW);	fn_Interface2.led_off(pedLeds, pedRED);	//Turn Off all PED's LEDs.
				}
				if (pedMode_active)
				{
					fn_Interface2.led_off(carLeds, carYLW); //Turn off Car Yellow Led
					fn_Interface3.led_on(carLeds, carRED); //Turn on Car Red Led
					//*******************************************************************************************
					fn_Interface2.led_off(pedLeds, pedYLW); //Turn off Ped Yellow Led
					fn_Interface3.led_on(pedLeds, pedGRN); //Turn on Ped Green Led
					//*********************
					pedMode_iterCount++;
					if(pedMode_iterCount == 2 && pressedAtState0)
					{
						pedMode_active = 0;
						endOfStates = 1;
					}
					else if (pedMode_iterCount == 1 && pressedAtState1)
					{
						pedMode_active = 0;
						endOfStates = 1;
					}
					else if (pedMode_iterCount == 1 && pressedAtState2)
					{
						pedMode_active = 0;
						endOfStates = 1;
					}
				}
				else
				{
					fn_Interface2.led_off(carLeds, carYLW); //Turn off Car Yellow Led
					fn_Interface3.led_on(carLeds, carRED); //Turn on Car Red Led
				}	
				state++;
				break;
			case 2:
				if (pedMode_iterCount == 2 && pressedAtState0)
				{
					pedMode_iterCount = 0;
				}
				else if (pedMode_iterCount == 1 && pressedAtState1)
				{
					pedMode_iterCount = 0;
				}
				else if (pedMode_iterCount == 1 && pressedAtState2)
				{
					pedMode_iterCount = 0;
				}
				if (pedMode_active)
				{
					fn_Interface2.led_off(carLeds, carRED); //Turn off Car Red Led
					fn_Interface3.led_on(carLeds, carYLW); //Turn on Car Yellow Led
					//*******************************************************************************************
					fn_Interface2.led_off(pedLeds, pedGRN); //Turn off Ped Green Led	
					fn_Interface3.led_on(pedLeds, pedYLW); //Turn on Ped Yellow Led
					//*********************
					pedMode_iterCount++;
					if(pedMode_iterCount == 2)
					{
						pedMode_active = 0;
					}
				}
				else if (endOfStates)
				{
					fn_Interface2.led_off(carLeds, carRED); //Turn off Car Red Led
					fn_Interface3.led_on(carLeds, carYLW); //Turn on Car Yellow Led
					//*******************************************************************************************	
					fn_Interface3.led_on(pedLeds, pedYLW); //Turn on Ped Yellow Led
				}
				else
				{
					fn_Interface2.led_off(carLeds, carRED); //Turn off Car Red Led
					fn_Interface3.led_on(carLeds, carYLW); //Turn on Car Yellow Led
				}
				state++;
				break;
			case 3:
				if (endOfStates)
				{
					fn_Interface2.led_off(pedLeds, pedGRN);	fn_Interface2.led_off(pedLeds, pedYLW);
					fn_Interface3.led_on(pedLeds, pedRED);
				}
				if (pedMode_iterCount == 2)
				{
					pedMode_iterCount = 0;
					fn_Interface2.led_off(pedLeds, pedGRN);	fn_Interface2.led_off(pedLeds, pedYLW);	fn_Interface2.led_off(pedLeds, pedRED);	//Turn Off all PED's LEDs.
				}
				fn_Interface2.led_off(carLeds, carYLW); //Turn off Car Yellow Led
				fn_Interface3.led_on(carLeds, carGRN); //Turn on Car Green Led
				endOfStates = 0;
				state = 0;
				break;
		}
	}
}