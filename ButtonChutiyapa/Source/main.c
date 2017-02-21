#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

int mode = 0,x = 0,y=0;

int map(int x, int in_min, int in_max, int out_min, int out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void main(void)
{
	sei();

	//INTERRUPT
	PORTD |= 1<<PIND3;
	GICR |= 1<<INT1;
	DDRD |= 1<<PORTD4 | 1<<PORTD5;
	//ADC
	ADMUX |= 1<<REFS0;
	ADCSRA |= 1<<ADEN | 1<<ADIE | 1<<ADPS2 | 1<<ADSC;

	//16 BIT TIMER
	TCCR1A |= 1<<COM1A1 | 1<<WGM11 | 1<<COM1B1;
	TCCR1B |= 1<<WGM12 | 1<<WGM13 | 1<<CS10;
	ICR1 = 255;
	x = x/1023*255;

	while(1)
	{
		if(mode==0)
		{
			OCR1A = x;
			y = x;
		}
		/*else if(mode==1)
		{
			OCR1B = x;
			OCR1A = y;
		}
		else
		{
			OCR1A = 255 - x;
			OCR1B = x;
		}*/
	}

}

ISR(ADC_vect)
{
	uint8_t low = ADCL;
	uint16_t t = ADCH << 8 | low;
	x = t;
	ADCSRA |= 1<<ADSC;
}

ISR(INT1_vect)
{
	if(mode==0) mode = 1;
	else if(mode==1) mode = 2;
	else mode = 0;
}
