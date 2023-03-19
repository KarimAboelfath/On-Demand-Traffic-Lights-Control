/*
 * registers.h
 *
 * Created: 1/19/2023 12:16:09 PM
 *  Author: Karim Nasr
 */ 

/************************************************************************/
/* This is the lowest abstraction layer.                                                                     */
/************************************************************************/
#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "utilities.h"
#include "myTypedefs.h"

//Global Variables
volatile uint8_t state;
volatile uint8_t pedMode_active;
volatile uint8_t endOfStates;
volatile uint8_t pressedAtState0;
volatile uint8_t pressedAtState1;
volatile uint8_t pressedAtState2;
volatile uint8_t resetOverFlowOrder;

/************************************************************************/
/* DIO Register                                                         */
/************************************************************************/
//PORTA Registers
#define PORTA *((volatile uint8_t*)0x3B) // 8-bit Register
#define DDRA  *((volatile uint8_t*)0x3A) // 8-bit Register
#define PINA  *((volatile uint8_t*)0x39) // 8-bit Register

//PORTB Registers
#define PORTB *((volatile uint8_t*)0x38) // 8-bit Register
#define DDRB  *((volatile uint8_t*)0x37) // 8-bit Register
#define PINB  *((volatile uint8_t*)0x36) // 8-bit Register

//PORTD Registers
#define PORTD *((volatile uint8_t*)0x32) // 8-bit Register
#define DDRD  *((volatile uint8_t*)0x31) // 8-bit Register
#define PIND  *((volatile uint8_t*)0x30) // 8-bit Register

/************************************************************************/
/* Timer0 Registers                                                     */
/************************************************************************/
#define TCCR0 *((volatile uint8_t*)0x53) //8-bit register
#define TCNT0 *((volatile uint8_t*)0x52) //8-bit register
#define TIFR  *((volatile uint8_t*)0x58) //8-bit register
#define OCR0  *((volatile uint8_t*)0x5C) //8-bit register
#define TIMSK *((volatile uint8_t*)0x59) //8-bit register

/************************************************************************/
/* Interrupts Registers                                                 */
/************************************************************************/
#define SREG  *((volatile uint8_t*)0x5F) //8-bit register
#define MCUCR *((volatile uint8_t*)0x55) //8-bit register
#define GICR *((volatile uint8_t*)0x5B) //8-bit register

/************************************************************************/
/* Ports and Pins Connections                                                          */
/************************************************************************/
#define carLeds 'A'
#define pedLeds 'B'
#define carGRN	0
#define carYLW	1
#define carRED	2
#define pedGRN	0
#define pedYLW	1
#define pedRED	2

#define Actual_buttonPort 'D'
#define Actual_buttonPin  2

#endif /* REGISTERS_H_ */