#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

void main(void)
{

	DDRD |= 1<<PIND4;

	TCCR1A |= 1<<COM1A1 | 1<<WGM11;
	TCCR1B |= 1<<WGM12 | 1<<WGM13 | 1<<CS10;
	ICR1 = 255;

	while(1)
	{
		OCR1B = 100;
		_delay_ms(100);
		OCR1B = 200;
		_delay_ms(100);
	}
}
