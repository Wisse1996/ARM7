
#pragma once


/*** initializes the pins for spi ***/
void init_SPI(void);

/*** function prototype for the reading of the temperature.  ***/
unsigned short readLM95071SPI(void);

