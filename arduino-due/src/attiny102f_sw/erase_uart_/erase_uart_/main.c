#include <atmel_start.h>
#include <stdio.h>
#include <string.h>
#include <usart_basic.h>
#include <atomic.h>
#include <util/delay.h>


int main(void)
{
	uint8_t i;
	static uint8_t rx[16];
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	ENABLE_INTERRUPTS();
	
	/* Replace with your application code */
	while (1) {

		// Initialize rx buffer so strncmp() check will work
		memset(rx, 0, sizeof(rx));
		for (i = 0; i < strlen("Atk"); i++) {
			rx[i] = USART_0_read(); // Blocks until character is available
		}

		// Compare received and expected data
		if (strncmp("Atk", (char *)rx, strlen("Atk")) != 0)
		{
			erase_payload_set_level(
			// <y> Initial level
			// <id> pad_initial_level
			// <false"> Low
			// <true"> High
			false);
		}
		else
		{
			erase_payload_set_level(
			// <y> Initial level
			// <id> pad_initial_level
			// <false"> Low
			// <true"> High
			true);
		}
	}
	return 0;
}
