#include "MCB2300 evaluationboard.h"
void initEvaluationBoard(void) {
	PINSEL10 = 0; // Disable ETM interface, enable LEDs
	FIO2DIR0 = 0xFF; // LEDS
	FIO0DIR3 = 0xFF;
	PINMODE4 = 0x0020AAAA;
	SCS = 1; // enable fast GPIO
	LEDS = 0x00; // on reset all leds are off

	// make sure all 4 timers are activited at power on
	PCONP |= (1 << 1);
	PCONP |= (1 << 2);
	PCONP |= (1 << 22);
	PCONP |= (1 << 23);

	lcd_init();
}

