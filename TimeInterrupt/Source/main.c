#include<avr/io.h>
#include<avr/interrupt.h>

int main(void)
{
	sei();
	DDRB |= 1<<PINB0 | 1<<PINB4;
	TCCR1B |= 1<<CS10 | 1<<CS11 | 1<<WGM12;
	TIMSK |= 1<<OCIE1A | 1<<OCIE1B;
	OCR1A = 31250;
	OCR1B = 15624;

	while(1)
	{
	}

}
ISR(TIMER1_COMPA_vect)
{
	PORTB ^= 1<<PINB0;
}
ISR(TIMER1_COMPB_vect)
{
	PORTB ^= 1<<PINB4;
}
