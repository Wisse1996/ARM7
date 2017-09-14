#include "MCB2300 evaluationboard.h"  // hardware related functions 
#include <stdbool.h> // bool C99

/*** global ***/
bool t0;

/************** interrupt service routine timer0 ******************/ 
__irq void T0_ISR (void) { 
	t0 = !t0;

	// interrupt code
	T0IR        = 1;	// Clear interrupt flag 
	VICVectAddr = 0;	// Update interrupt priority hardware 
} 
 
/********************  initializing timer0 ************************/ 
void init_T0(void) { 
	T0MR0 = 100000; 
	T0MCR = 3;	// Enable interrupt, reset on match register 0 
	T0TCR = 1;	// Enable timer0
	VICVectAddr4 = (unsigned long)T0_ISR;	// Set interrupt vector 
	VICVectPriority4 = 9;	// Set to priority 10 (arbitrary value) 
	VICIntEnable  = (1 << 4);	// Enable Ttimer0 Interrupt 
} 
