/*
 * interrupts.h
 *
 * Created: 1/23/2023 1:03:04 PM
 *  Author: Karim Nasr
 */ 

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "../../Utilities/registers.h"

// all internal driver typedefs
//Type definitions of structs which contain pointer to functions in a higher abstraction layer (function containers)
typedef struct {
	uint8_t (*led_toggle)(uint8_t, uint8_t);
} fn_Ptr_t;

typedef struct {
	uint8_t (*led_off)(uint8_t, uint8_t);
} fn_Ptr2_t;

typedef struct {
	uint8_t (*led_on)(uint8_t, uint8_t);
} fn_Ptr3_t;

typedef struct {
	uint8_t (*pedMode_callback)(void);
} fn_Ptr4_t;

//Declare the function containers (structs type definitions)
fn_Ptr_t fn_Interface;
fn_Ptr2_t fn_Interface2;
fn_Ptr3_t fn_Interface3;
fn_Ptr4_t fn_Interface4;

// all driver macros
//Timer0 Overflow Interrupt Vector
#define TIMER0_OVF_vect __vector_11
//INT0 External Interrupt Vector
#define INT0_vect __vector_1

// all driver function prototypes
uint8_t INT0_externalInterrupt_init_risingEdge(void);

//ISR Macro Define:
#define ISR(INT_VECT)void INT_VECT(void) __attribute__ ((signal, used));\
void INT_VECT(void)

#endif /* INTERRUPTS_H_ */