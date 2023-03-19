/*
 * On-demand Traffic light control.c
 *
 * Created: 1/19/2023 5:00:18 AM
 * Author : Karim Nasr
 */
 
#include "Application/application.h"	//Include application.h (which is the highest abstraction layer)

#define F_CPU 8000000UL  // Set CPU clock frequency to 8 Mhz

void DIO_driver_test_module(void);

int main(void)
{
	//Define pointers to the functions interfaces and initialize them with the addresses of the higher-layer functions implementations.
	fn_Interface.led_toggle = LED_toggle;
	fn_Interface2.led_off = LED_off;
	fn_Interface3.led_on = LED_on;
	fn_Interface4.pedMode_callback = pedMode;

	//Initialize the LEDs.
	LED_init(carLeds, carGRN);
	LED_init(carLeds, carYLW);
	LED_init(carLeds, carRED);
	LED_init(pedLeds, pedGRN);
	LED_init(pedLeds, pedYLW);
	LED_init(pedLeds, pedRED);
	
	//Initialize the push button.
	BUTTON_init(Actual_buttonPort, Actual_buttonPin);
	
	//Initialize external interrupt 0 with a rising edge trigger.
	INT0_externalInterrupt_init_risingEdge();
	
    while (1)	//Main loop
    {
		start_application();	//start the application
		//DIO_driver_test_module();
	}
}

void DIO_driver_test_module(void)
{
	/************************************************************************/
	/* This DIO test module includes all the test functions for the corresponding DIO driver functions 
	   This function takes no input, turns on a Blue LED on Port B Pin 7, if all the function tests are passed successfully and turns it off, if there is an error.*/
	/************************************************************************/
	volatile static uint8_t feedbackLEDstate = 1;
	volatile  uint8_t numberOfPassedTests = 0;
	
	// Test functions definitions
	void DIO_init_test_function(void)
	{
		/************************************************************************/
		/* This function tests the DIO_init function.
		   This function takes no input, increments the number of passed tests by one if the function test is passed. 
		   What it does is that it initializes an arbitrary pin in a port as output first, then initializes it as input, then
		   it initialized it as output again. It tests if the previous initializations were done successfully or not. 
		   It also tests if the direction value inputted is invalid.                          */
		/************************************************************************/
		uint8_t portNumber = PORT_B;
		uint8_t pinNumber = 6;
		uint8_t direction = OUT;
	
		// Test output pin initialization
		uint8_t result = DIO_init(portNumber, pinNumber, direction);
		if (result != 1 || !(DDRB & (1 << pinNumber)))
		{
			// Failed to initialize output pin
			feedbackLEDstate = 0;
		}
		
		// Test input pin initialization
		direction = IN;
		result = DIO_init(portNumber, pinNumber, direction);
		if (result != 1 || (DDRB & (1 << pinNumber)))
		{
			// Failed to initialize input pin
			feedbackLEDstate = 0;
		}
	
		// Test output pin initialization again
		direction = OUT;
		result = DIO_init(portNumber, pinNumber, direction);
		if (result != 1 || !(DDRB & (1 << pinNumber)))
		{
			// Failed to initialize output pin
			feedbackLEDstate = 0;
		}
		
		// Test invalid direction argument
		direction = 2; // Invalid value
		result = DIO_init(portNumber, pinNumber, direction);
		if (result != 0) {
			// Failed to return error for invalid direction argument
			feedbackLEDstate = 0;
		}
		
		//Increment the number of passed tests by one this function tests are passed
		if (feedbackLEDstate){numberOfPassedTests++;}
	}
	void DIO_write_test_function(void)
	{
		/************************************************************************/
		/* This function tests the DIO_write function.
		   This function takes no input, increments the number of passed tests by one if the function test is passed. 
		   What it does is that it initializes an arbitrary pin in a port as output first, then writes 1 on it, then
		   writes 0 on it, then writes 1 on it again. It tests if the previous write operations were done successfully or not. 
		   It also tests if the value argument inputted is invalid.                          */
		/************************************************************************/
		uint8_t portNumber = PORT_B;
		uint8_t pinNumber = 6;
		uint8_t value = HIGH;
		
		//Initialize the specified pin as output
		DIO_init(portNumber, pinNumber, OUT);
	
		// Test writing 1 on output pin
		uint8_t result = DIO_write(portNumber, pinNumber, HIGH);
		if (result != 1 || !(PORTB & (1 << pinNumber)))
		{
			// Failed to write 1 on output pin
			feedbackLEDstate = 0;
		}
		
		// Test writing 0 on output pin
		value = LOW;
		result = DIO_write(portNumber, pinNumber, value);
		if (result != 1 || (PORTB & (1 << pinNumber)))
		{
			// Failed to write 0 on output pin
			feedbackLEDstate = 0;
		}
	
		// Test writing 1 on output pin again
		value = HIGH;
		result = DIO_write(portNumber, pinNumber, value);
		if (result != 1 || !(PORTB & (1 << pinNumber)))
		{
			// Failed to write 1 on output pin
			feedbackLEDstate = 0;
		}
		
		// Test invalid value argument
		value = 2; // Invalid value
		result = DIO_write(portNumber, pinNumber, value);
		if (result != 0) {
			// Failed to return error for invalid value argument
			feedbackLEDstate = 0;
		}
		
		//Increment the number of passed tests by one this function tests are passed
		if (feedbackLEDstate){numberOfPassedTests++;}
	}
	void DIO_toggle_test_function(void)
	{
		/************************************************************************/
		/* This function tests the DIO_toggle function.
		   This function takes no input, increments the number of passed tests by one if the function test is passed. 
		   What it does is that it initializes an arbitrary pin in a port as output first, then writes 0 on it, then
		   toggles it from 0 to 1, then from 1 to 0, then from 0 to 1 again. It tests if the previous toggling operations were done successfully or not. 
		   It also tests if the portNumber argument value inputted is invalid.                          */
		/************************************************************************/
		uint8_t portNumber = PORT_B;
		uint8_t pinNumber = 6;
		
		//Initialize the specified pin as output
		DIO_init(portNumber, pinNumber, OUT);
		
		//Write 0 on the specified output pin
		DIO_write(portNumber, pinNumber, LOW);
		
		// Test toggling the pin form LOW to HIGH
		uint8_t result = DIO_toggle(portNumber, pinNumber);
		if (result != 1 || !(PORTB & (1 << pinNumber)))
		{
			// Failed to toggle output pin to be have value 1 written on it
			feedbackLEDstate = 0;
		}
		
		// Test toggling the pin form HIGH to LOW
		result = DIO_toggle(portNumber, pinNumber);
		if (result != 1 || (PORTB & (1 << pinNumber)))
		{
			// Failed to toggle output pin to be have value 0 written on it
			feedbackLEDstate = 0;
		}
		
		// Test toggling the pin form LOW to HIGH again
		result = DIO_toggle(portNumber, pinNumber);
		if (result != 1 || !(PORTB & (1 << pinNumber)))
		{
			// Failed to toggle output pin to be have value 1 written on it
			feedbackLEDstate = 0;
		}
		
		// Test invalid portNumber argument
		result = DIO_toggle(5, pinNumber);
		if (result != 0)
		{
			// Failed to return error for invalid portNumber argument
			feedbackLEDstate = 0;
		}
		
		//Increment the number of passed tests by one this function tests are passed
		if (feedbackLEDstate){numberOfPassedTests++;}
	}
	void DIO_read_test_function(void)
	{
		/************************************************************************/
		/* This function tests the DIO_read function.
		   This function takes no input, increments the number of passed tests by one if the function test is passed. 
		   What it does is that it initializes an arbitrary pin in a port as output first, then writes 1 on it, then
		   reads the value on the input pin and checks if it is actually 1, then it it initializes another arbitrary pin in a port as output first, then writes 0 on it, then
		   reads the value on the other input pin and checks if it is actually 0. It tests if the previous readings were correct or not. 
		   It also tests if the portNumber argument value inputted is invalid.                          */
		/************************************************************************/
		uint8_t portNumber = PORT_B;
		uint8_t pinNumber1 = 5;
		uint8_t value1;
		uint8_t pinNumber2 = 6;
		uint8_t value2;
		
		// Test reading from the specified pin when it is high
		DIO_init(portNumber, pinNumber1, OUT);	//Initialize the specified pin as input
		DIO_write(portNumber, pinNumber1, HIGH);	//Write 1 on the specified input pin
		DIO_init(portNumber, pinNumber1, IN);	//Initialize the specified pin as input
		uint8_t result1 = DIO_read(portNumber, pinNumber1, &value1);
		if (result1 != 1 || value1 != 1)
		{
			// Test failed: expected value is 1, but got a zero value
			feedbackLEDstate = 0;
		}
		
		// Test reading from the specified pin when it is low
		DIO_init(portNumber, pinNumber2, OUT);	//Initialize the specified pin as input
		DIO_write(portNumber, pinNumber2, HIGH);	//Write 0 on the specified input pin
		DIO_init(portNumber, pinNumber2, IN);	//Initialize the specified pin as input
		uint8_t result2 = DIO_read(portNumber, pinNumber2, &value2);
		if (result2 != 1 || value2 != 1)
		{
			// Test failed: expected value is 1, but got a zero value
			feedbackLEDstate = 0;
		}
		
		// Test invalid portNumber argument
		result1 = DIO_read(5, pinNumber1, &value1);
		if (result1 != 0)
		{
			// Failed to return error for invalid portNumber argument
			feedbackLEDstate = 0;
		}
		
		//Increment the number of passed tests by one this function tests are passed
		if (feedbackLEDstate){numberOfPassedTests++;}
	}
	
	DIO_init_test_function();	// Run the first function test
	if (numberOfPassedTests == 1){DIO_write_test_function();}	// if the previous test is passed, run the next test
	if (numberOfPassedTests == 2){DIO_toggle_test_function();}		// if the previous test is passed, run the next test
	if (numberOfPassedTests == 3){DIO_read_test_function();}	// if the previous test is passed, run the next test
		
	// Turn on or off the feedback blue LED depending on if all the function tests are passed or not
	LED_init(PORT_B, 7);
	if (numberOfPassedTests == 4){LED_on(PORT_B, 7);}else{LED_off(PORT_B, 7);}
}