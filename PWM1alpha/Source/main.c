#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

int x = 0,y = 0,mode = 0;

void main(void)
{
	sei();
	//LED Pins
	DDRD |= 1<<PIND5 | 1<<PIND7;
	DDRB |= 1<<PINB0;

	//ADC
	ADMUX |= 1<<REFS0;
	ADCSRA |= 1<<ADIE | 1<<ADPS2 | 1<<ADEN | 1<<ADSC;

	//16BIT TIMER
	TCCR1A |= 1<<COM1A1 | 1<<COM1B1 | 1<<WGM11;
	TCCR1B |= 1<<WGM12 | 1<<WGM13 | 1<<CS10;
	ICR1 = 1023;
	//OCR1A AND OCR1B

	//INTERRUPT
	PORTD |= 1<<PIND3;
	GICR |= 1<<INT1;
	MCUCR |= 1<<ISC11;

	//8BIT TIMER
	TCCR2 |= 1<<WGM20 | 1<<WGM21 | 1<<COM21 | 1<<CS20;

	while(1)
	{

		if(mode==0)
		{
			OCR1A = x;
			OCR2 = 0;
		}
		else if(mode==1)
		{
			OCR2 = y;
			OCR1A = 0;
		}
		else
		{
			OCR1A = 1023 - x;
			OCR2 = y;
		}

	}

}

ISR(ADC_vect)
{
	uint8_t low = ADCL;
	uint16_t t = ADCH<<8 | low;
	switch(ADMUX)
	{
	case 0x40:
		x = t;///1023*20000;
		ADMUX = 0x41;
		break;

	case 0x41:
		y = t;///1023*20000;
		ADMUX = 0x40;
		break;
	}
	y = x/1023.0*255;
	ADCSRA |= 1<<ADSC;
}

ISR(INT1_vect)
{
	_delay_ms(30);
	if(bit_is_clear(PIND,3))
	{
		PORTB ^= 1<<PINB0;
		if(mode==0)mode = 1;
		else if(mode==1)mode = 2;
		else mode = 0;
	}
}
