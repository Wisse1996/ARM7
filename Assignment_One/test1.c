/* ******************** Workshop 1 -- Exercise 2 **************************/
#include <stdio.h> // standard C definitions
#include "MCB2300 evaluationboard.h" // hardware related functions


int main(void) {
	initEvaluationBoard();
	
	char *test = "HANZE!";
	lcd_print(test);
	
	int timer = 100;

	while (1) {
		FIO0SET3 = 0xFF;
		//FIO0SET = 0xFFFFFFFF;
		LEDS = 1;
		for (int i = 0; i < timer; i++) {
		}
		
		FIO0CLR3 = 0xFF;
		//FIO0CLR = 0xFFFFFFFF;
		LEDS = 0;
		for (int i = 0; i < timer; i++) {
		}
		
		timer++;
		
	}	
}
