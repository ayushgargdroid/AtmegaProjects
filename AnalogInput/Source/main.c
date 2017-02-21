#include<avr/io.h>
#include<avr/interrupt.h>

int count = 0;
int main(void)
{
	sei();
	DDRB |= 1<<PINB0;
	ADMUX |= 1<<REFS0;
	ADCSRA |= 1<<ADEN | 1<<ADSC | 1<<ADIE | 1<<ADPS2;

	while(1)
	{

	}
}

ISR(ADC_vect)
{
	uint8_t low = ADCL;
	uint16_t t= ADCH << 8 | low;
	if(t<512)
	{
		count++;
		if(count>1000)
		{
			PORTB ^= 1<<PINB0;
			count = 0;
		}
	}
	ADCSRA |= 1<<ADSC;
}
