/* ******************** Workshop 1 -- Exercise 2 **************************/
#include <stdio.h> // standard C definitions
#include "MCB2300 evaluationboard.h" // hardware related functions

	char *test = "HANZE?";

int main(void) {
	initEvaluationBoard();
	lcd_print(test);
	while (1) {
		if (INT0) {
			LEDS = 0x0F;
			BUZZER = 0xFF;
		}			else {
			LEDS = 0xF0;
			BUZZER = 0x00;
		}
	}	
}
