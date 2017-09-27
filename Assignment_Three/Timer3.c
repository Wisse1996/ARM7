#include "MCB2300 evaluationboard.h"  // hardware related functions
#include <stdbool.h> // bool C99


/************** interrupt service routine timer3 ******************/
__irq void T3_ISR (void) {
}

/********************  initializing timer3 ************************/
void init_T3(void) {
	T3MR0 = 1500000 - 1; // set on 1 second?
	T3MCR |= (1 << 0);	// Enable interrupt -> DS 557
	T3TCR = 1;	// Enable timer3
	VICVectAddr27 = (unsigned long)T3_ISR;	// Set interrupt vector
	VICVectPriority27 = 7;	// Set to priority 10 (arbitrary value)
	VICIntEnable  = (1 << 27);	// Enable Ttimer3 Interrupt
}
