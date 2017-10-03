#include "MCB2300 evaluationboard.h"
void initEvaluationBoard(void) {
	PINSEL10 = 0; // Disable ETM interface, enable LEDs
	//FIO2DIR0 = 0xFF; // LEDS
	//FIO0DIR3 = 0xFF; // BUZZER
	//PINMODE4 = 0x0020AAAA; // LEDS
	SCS |= (1 << 0); // enable fast GPIO !!!
	//LEDS = 0x00; // on reset all leds are off
//	BUZZER = 0x00; // BUZZER off at start

	// init the lcd
	lcd_init();
}

