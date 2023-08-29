/*
 * GccApplication1.c
 *
 * Created: 29.08.2023 09:41:44
 * Author : pmherdle
 */ 

#define F_CPU 419200UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 0x0;

while (1)
{
	PORTB |= (1 << PB0);

	_delay_ms(10000);

	PORTB &= (0 << PB0);
	
	_delay_ms(10000);
	
}
	return 0;
}

