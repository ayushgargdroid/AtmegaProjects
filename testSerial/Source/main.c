#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

unsigned char rec = '0';int top=-1;


void main(void)
{
	sei();
	DDRB |= 1<<PINB0;

	//USART COMMUNICATION
	UCSRA |= 1<<U2X;
	UCSRB |= 1<<RXCIE | 1<<RXEN | 1<<TXEN;
	UCSRC |= 1<<UCSZ0 | 1<<UCSZ1;
	int ubr = 12;
	UBRRH = (unsigned char)(ubr>>8);
	UBRRL = (unsigned char)ubr;
	int i=0;

	while(1)
	{
		while (! (UCSRA & (1 << UDRE)) );
			UDR = (unsigned char)rec;

		i =(rec - '0');
		while(i!=0)
		{
			PORTB |= 1<<PINB0;
			_delay_ms(100);
			PORTB &= ~(1<<PINB0);
			_delay_ms(100);
			i--;
		}
		i = 0;
		rec = '0';
	}

}

ISR(USART_RXC_vect)
{
	rec = (unsigned char)UDR;
}
