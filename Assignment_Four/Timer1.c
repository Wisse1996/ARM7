#include "MCB2300 evaluationboard.h"  // hardware related functions
#include <stdbool.h> // bool C99

extern bool timeFlag, resetY;
extern int k;
extern int time[12];
bool delay = true;


/************** interrupt service routine timer1 ******************/
__irq void T1_ISR (void) {

	if (delay) {
		T0TCR = 0;
		T1MR0 = 1200000;
		delay= false;
	} else {
		delay = true;
		T0TCR = 1;
		resetY = true;
		if (k == 10) {
			k = 0;
		} else {
			k++;
		}
		//timeFlag = true;
		T1MR0 = time[k];
	}

	//T1MR0 -= 50000;
	// interrupt code
	T1IR        = 1;	// Clear interrupt flag
	VICVectAddr = 0;	// Update interrupt priority hardware
}

/********************  initializing timer1 ************************/
void init_T1(void) {
	T1MR0 = time[0] - 1;
	T1MCR = 3;	// Enable only interrupt -> DS 557 | stop and interrupt
	T1TCR = 1;	// Enable timer1
	VICVectAddr5 = (unsigned long)T1_ISR;	// Set interrupt vector
	VICVectPriority5 = 8;	// Set to priority 10 (arbitrary value)
	VICIntEnable  = (1 << 5);	// Enable Ttimer1 Interrupt
}
