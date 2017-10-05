#include "MCB2300 evaluationboard.h"  // hardware related functions
#include <stdbool.h> // bool C99


/*** global ***/
extern bool timeFlag;


/************** interrupt service routine timer1 ******************/
__irq void T1_ISR (void) {
	timeFlag = true;

	// interrupt code
	T1IR        = 1;	// Clear interrupt flag
	VICVectAddr = 0;	// Update interrupt priority hardware
}

/********************  initializing timer1 ************************/
void init_T1(void) {
	// T1MR0 = time[0];
	T1MCR = 3;	// Enable only interrupt -> DS 557 | stop and interrupt
	T1TCR = 1;	// Enable timer1
	VICVectAddr5 = (unsigned long)T1_ISR;	// Set interrupt vector
	VICVectPriority5 = 8;	// Set to priority 10 (arbitrary value)
	VICIntEnable  = (1 << 5);	// Enable Ttimer1 Interrupt
}
