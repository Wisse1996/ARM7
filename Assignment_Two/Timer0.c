#include "MCB2300 evaluationboard.h"  // hardware related functions
#include <stdbool.h> // bool C99
#include "time.h"
/*** global ***/
extern struct *Time mainTime;
extern bool isRunning;

/************** interrupt service routine timer0 ******************/
__irq void T0_ISR (void) {
	// program code
        if (mainTimerActive) {
            mainTime = increaseTimer(mainTime);
            // TODO delay with for loop
        }
	// interrupt code
	T0IR        = 1;	// Clear interrupt flag
	VICVectAddr = 0;	// Update interrupt priority hardware
}

/********************  initializing timer0 ************************/
void init_T0(void) {
	T0MR0 = 500000;
	T0MCR = (1 << 0);	// Enable interrupt -> DS 557
	//T0TCR = 1;	// Enable timer0
	VICVectAddr4 = (unsigned long)T0_ISR;	// Set interrupt vector
	VICVectPriority4 = 9;	// Set to priority 10 (arbitrary value)
	VICIntEnable  = (1 << 4);	// Enable Ttimer0 Interrupt
}
