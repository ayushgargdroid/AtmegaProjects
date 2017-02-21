#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

unsigned char rec;

void main(void)
{
	sei();
	DDRB = 0b00000111;
	PORTB = 0b00000000;

	int ubrrv = 6; //Calculated for 9600 on 1Mhz
	UBRRH = (unsigned char)(ubrrv>>8);
	UBRRL = (unsigned char)ubrrv;
	UCSRC |= 1<<URSEL | 3<<UCSZ0;
	UCSRB |= 1<<RXEN | 1<<TXEN | 1<<RXCIE | 1<<TXCIE;

	while(1)
	{
		PORTB ^= 1<<PINB1;
		_delay_ms(100);
		while(!(UCSRA & (1<<UDRE)));
		UDR = 0b00001111;
	}
}

ISR(USART_RXC_vect)
{
	rec = UDR;
	PORTB ^= 1<<PINB2;
	_delay_ms(100);
	if(rec=='a')
	{
		PORTB &= ~(1<<PINB1);
		_delay_ms(1000);
	}
}
ISR(USART_TXC_vect)
{
	PORTB ^= 1<<PINB0;
	//_delay_ms(100);
}
