#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

unsigned char rec;

void main(void)
{
	sei();
	DRRB |= 1<<PINB0 | 1<<PINB1 | 1<<PINB2;

	//USART Communication
	UCSRB |= 1<<RXCIE | 1<<RXEN | 1<<TXEN;
	UCSRC |= 1<<UCSZ1 | 1<<UCSZ0;
	int u = 6;
	UBRRH = (unsigned char)(u>>8);
	UBRRL = (unsigned char)u;

	while(1)
	{

	}
}
ISR(USART_RXC_vect)
{
	rec = UDR;
	PORTB ^= 1<<PINB0;
	if(rec=='a')
	{
		PORTB ^= 1<<PINB1;
		_delay_ms(100);
	}
}
