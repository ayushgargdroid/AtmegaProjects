#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

int x = 0;
int y = 0;

void main(void)
{
	sei();
	DDRD |= 1<<PORTD4 | 1<<PORTD7;
	TCCR1A |= 1<<COM1B1 | 1<<WGM11;
	TCCR1B |= 1<<WGM12 | 1<<WGM13 | 1<<CS10;

	ADMUX = 0x40;
	ADCSRA |= 1<<ADEN | 1<<ADIE | 1<<ADSC | 1<<ADPS2;

	TCCR2 |= 1<<WGM21 | 1<<WGM20 | 1<<COM21 | 1<<CS20;

	ICR1 = 255;
	x = x/1023*255;

	while(1)
	{
		//if(TCNT2 >= 1000) TCNT2 = 0;
		OCR2 = x;
		OCR1B = y;
	}

}

ISR(ADC_vect)
{
	uint8_t low = ADCL;
	uint16_t t= ADCH << 8 | low;
	switch(ADMUX)
	{
	case 0x40 :
		x = t;
		ADMUX = 0x41;
		break;
	case 0x41 :
		y = t;
		ADMUX = 0x40;
		break;
	}
	ADCSRA |= 1<<ADSC;

}
