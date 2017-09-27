#include "MCB2300 evaluationboard.h"  // hardware related functions
#include <stdbool.h> // bool C99
#include "time.h"

/************** interrupt service routine timer1 ******************/
__irq void T1_ISR (void) {
}

/********************  initializing timer1 ************************/
void init_T1(void) {
	T1MR0 = 3000000 - 1;
	T1MCR = (1 << 0);	// Enable only interrupt -> DS 557
	T1TCR = 0;	// Enable timer1
	VICVectAddr5 = (unsigned long)T1_ISR;	// Set interrupt vector
	VICVectPriority5 = 8;	// Set to priority 10 (arbitrary value)
	VICIntEnable  = (1 << 5);	// Enable Ttimer1 Interrupt
}
