#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

void main(void)
{
	DDRD |= 1<<PORTD5 | 1<<PORTD7;
	DDRB |= 1<< PINB0;
	TCCR1A |= 1<<COM1A1  | 1<<COM1B1 | 1<<WGM11;
	TCCR1B |= 1<<WGM13 | 1<<CS10 | 1<<WGM12;
	ICR1 = 255;
	PORTB |= 1<<PINB0;
	//TCCR2 |= 1<<WGM21 | 1<<WGM20 | 1<<COM21 | 1<<CS20 | 1<<CS21;
	//int t = 15000;
	OCR1A = 255;

	while(1)
	{
		/*OCR1A = t;
		_delay_ms(1000);
		t+=10000;
		if(t>60000) t = 0;*/
	}

}
