#include "MCB2300 evaluationboard.h"  // hardware related functions
#include <stdbool.h> // bool C99
#include "time.h"

/*** global ***/

/************** interrupt service routine timer0 ******************/
__irq void T0_ISR (void) {


}

/********************  initializing timer0 ************************/
void init_T0(void) {
	T0MR0 = 24000 - 1;
	T0MCR = 3;//(1 << 0);	// Enable interrupt -> DS 557
	T0TCR = 0;	// Enable timer0
	VICVectAddr4 = (unsigned long)T0_ISR;	// Set interrupt vector
	VICVectPriority4 = 9;	// Set to priority 10 (arbitrary value)
	VICIntEnable  = (1 << 4);	// Enable Ttimer0 Interrupt
}
