#include <atmel_start.h>
#include <stdio.h>
#include <string.h>
#include <usart_basic.h>
#include <atomic.h>
#include <util/delay.h>

static uint8_t rx[16];
int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	ENABLE_INTERRUPTS();
	uint8_t i,j;
	
	/* Replace with your application code */
	while (1) {

		// Check that "hello" was received on loopback RX.
		// Initialize rx buffer so strncmp() check will work
		memset(rx, 0, sizeof(rx));
		for (i = 0; i < strlen("11"); i++) {
			rx[i] = USART_0_read(); // Blocks until character is available
		}
		
		for (i = 0; i < strlen("11"); i++){
			for (j=0; j<8; j++){
				
			}
		}

	}
	return 0;
}
