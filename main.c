/*
 * GccApplication1.c
 *
 * Created: 03.09.2023 15:34:17
 * Author : pmherdle
 */ 


#define F_CPU 419200UL
#include <avr/io.h>
#include <util/delay.h>
#define BAUD 9600
#define UBRR F_CPU / 16 / BAUD - 1
#include <stdio.h>





int main(void)
{
DDRB = 0x0;
while (1)
{
 	PORTB |= (1 << PB0);

 	_delay_ms(20000);

 	PORTB &= (0 << PB0);

 	_delay_ms(20000);

}
	return 0;
}






int main(void)
{
	char receivedData;

	// Initialize UART
	USART_Init(UBRR);

	// Redirect printf and scanf to UART
	uart_link_printf();

	// Send a welcome message
	printf("UART Test Program!\n");
	printf("Type any character and it will be echoed back.\n");

	while (1)
	{
		// Wait for a character from UART
		receivedData = USART_Receive();

		// Echo the received character back to the terminal
		printf("Received: %c\n", receivedData);
		
		
	}

	return 0; // This line will never be reached in an embedded program
}



void USART_Init( unsigned int ubrr )
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
}



void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}


void uart_link_printf() {
	fdevopen(&USART_Transmit, &USART_Receive);
}

