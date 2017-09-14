#include "MCB2300 evaluationboard.h"  // hardware related functions 
#include <stdbool.h> // bool C99

/*** global ***/
bool t3;

/************** interrupt service routine timer3 ******************/ 
__irq void T3_ISR (void) { 
	t3 = !t3;

	// interrupt code
	T3IR        = 1;	// Clear interrupt flag 
	VICVectAddr = 0;	// Update interrupt priority hardware 
} 
 
/********************  initializing timer3 ************************/ 
void init_T3(void) { 
	T3MR0 = 90000;
	T3MCR = 3;	// Enable interrupt, reset on match register 0 
	T3TCR = 1;	// Enable timer3
	VICVectAddr27 = (unsigned long)T3_ISR;	// Set interrupt vector 
	VICVectPriority27 = 7;	// Set to priority 10 (arbitrary value) 
	VICIntEnable  = (1 << 27);	// Enable Ttimer3 Interrupt 
} 
