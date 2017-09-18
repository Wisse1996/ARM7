#include "MCB2300 evaluationboard.h"  // hardware related functions
#include <stdbool.h> // bool C99
// Button listener //
/*** global ***/
extern int state;

/************** interrupt service routine timer3 ******************/
__irq void T3_ISR (void) {
	// program code
	if (!INT0) { // button is still pressed
		state = STOP;
	}

	// interrupt code
	T3IR        = 1;	// Clear interrupt flag
	VICVectAddr = 0;	// Update interrupt priority hardware
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
