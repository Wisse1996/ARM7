/* ******************** Workshop 1 -- Exercise 2 **************************/
#include <stdio.h> // standard C definitions
#include "MCB2300 evaluationboard.h" // hardware related functions

int main(void) {
	initEvaluationBoard();
	while (1) {
		int i;
		for (i = 0; i < 10; i++) {
			if (INT0) LEDS = 0x0F; else LEDS = 0xF0;
		}
	}
}
