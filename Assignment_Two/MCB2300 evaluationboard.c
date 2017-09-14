#include "MCB2300 evaluationboard.h"
void initEvaluationBoard(void) {
	PINSEL10 = 0; // Disable ETM interface, enable LEDs
	FIO2DIR0 = 0xFF; // LEDS
	FIO0DIR3 = 0xFF;
	PINMODE4 = 0x0020AAAA;
	SCS = 1;
	lcd_init();
	LEDS = 0x00; // on reset all leds are off
}

