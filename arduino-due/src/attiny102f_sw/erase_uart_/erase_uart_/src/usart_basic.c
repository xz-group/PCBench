/**
 * \file
 *
 * \brief USART basic driver.
 *
 (c) 2020 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/**
 * \defgroup doc_driver_usart_basic USART Basic
 * \ingroup doc_driver_usart
 *
 * \section doc_driver_usart_basic_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */
#include <compiler.h>
#include <clock_config.h>
#include <usart_basic.h>
#include <atomic.h>

/* Static Variables holding the ringbuffer used in IRQ mode */
static uint8_t          USART_0_rxbuf[USART_0_RX_BUFFER_SIZE];
static volatile uint8_t USART_0_rx_head;
static volatile uint8_t USART_0_rx_tail;
static volatile uint8_t USART_0_rx_elements;

void USART_0_default_rx_isr_cb(void);
void (*USART_0_rx_isr_cb)(void) = &USART_0_default_rx_isr_cb;

void USART_0_default_rx_isr_cb(void)
{
	uint8_t data;
	uint8_t tmphead;

	/* Read the received data */
	data = UDR;
	/* Calculate buffer index */
	tmphead = (USART_0_rx_head + 1) & USART_0_RX_BUFFER_MASK;

	if (tmphead == USART_0_rx_tail) {
		/* ERROR! Receive buffer overflow */
	} else {
		/* Store new index */
		USART_0_rx_head = tmphead;

		/* Store received data in buffer */
		USART_0_rxbuf[tmphead] = data;
		USART_0_rx_elements++;
	}
}



/* Interrupt service routine for RX complete */
ISR(USART_RXC_vect)
{
	if (USART_0_rx_isr_cb != NULL)
		(*USART_0_rx_isr_cb)();
}


bool USART_0_is_rx_ready()
{
	return (USART_0_rx_elements != 0);
}


/**
 * \brief Read one character from USART_0
 *
 * Function will block if a character is not available.
 *
 * \return Data read from the USART_0 module
 */
uint8_t USART_0_read(void)
{
	uint8_t tmptail;

	/* Wait for incoming data */
	while (USART_0_rx_elements == 0){
	}
	/* Calculate buffer index */
	tmptail = (USART_0_rx_tail + 1) & USART_0_RX_BUFFER_MASK;
	/* Store new index */
	USART_0_rx_tail = tmptail;
	ENTER_CRITICAL(R);
	USART_0_rx_elements--;
	EXIT_CRITICAL(R);

	/* Return data */
	return USART_0_rxbuf[tmptail];
}


/**
 * \brief Initialize USART interface
 * If module is configured to disabled state, the clock to the USART is disabled
 * if this is supported by the device's clock system.
 *
 * \return Initialization status.
 * \retval 0 the USART init was successful
 * \retval 1 the USART init was not successful
 */
int8_t USART_0_init()
{

	// Module is in UART mode

	/* Enable USART */
	PRR &= ~(1 << PRUSART);

#define BAUD 9600

#include <utils/setbaud.h>

	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;

	UCSRA = USE_2X << U2X /*  */
	        | 0 << MPCM;  /* Multi-processor Communication Mode: disabled */

	UCSRB = 1 << RXCIE    /* RX Complete Interrupt Enable: enabled */
	        | 0 << TXCIE  /* TX Complete Interrupt Enable: disabled */
	        | 0 << UDRIE  /* USART Data Register Empty Interupt Enable: disabled */
	        | 1 << RXEN   /* Receiver Enable: enabled */
	        | 0 << TXEN   /* Transmitter Enable: enabled */
	        | 0 << UCSZ2; /*  */

//	 UCSRC = (0 << UMSEL1) | (0 << UMSEL0) /*  */
//			 | (0 << UPM1) | (0 << UPM0) /* Disabled */
//			 | 0 << USBS /* USART Stop Bit Select: disabled */
//			 | (1 << UCSZ1) | (1 << UCSZ0); /* 8-bit */

//	 UCSRD = 0 << RXSIE /* USART RX Start Interrupt Enable: disabled */
//			 | 0 << SFDE; /* Start Frame Detection Enable: disabled */

	uint8_t x;

	/* Initialize ringbuffers */
	x = 0;

	USART_0_rx_tail     = x;
	USART_0_rx_head     = x;
	USART_0_rx_elements = x;

	return 0;
}

/**
 * \brief Enable RX and TX in USART_0
 * 1. If supported by the clock system, enables the clock to the USART
 * 2. Enables the USART module by setting the RX and TX enable-bits in the USART control register
 *
 * \return Nothing
 */
void USART_0_enable()
{
	UCSRB |= (1 << RXEN);
}

/**
 * \brief Enable RX in USART_0
 * 1. If supported by the clock system, enables the clock to the USART
 * 2. Enables the USART module by setting the RX enable-bit in the USART control register
 *
 * \return Nothing
 */
void USART_0_enable_rx()
{
	UCSRB |= (1 << RXEN);
}

/**
 * \brief Disable USART_0
 * 1. Disables the USART module by clearing the enable-bit(s) in the USART control register
 * 2. If supported by the clock system, disables the clock to the USART
 *
 * \return Nothing
 */
void USART_0_disable()
{
	UCSRB &= ~((1 << TXEN) | (1 << RXEN));
}

/**
 * \brief Get recieved data from USART_0
 *
 * \return Data register from USART_0 module
 */
uint8_t USART_0_get_data()
{
	return UDR;
}
