#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
void main(void)
{
	DDRB |= 1<<PINB0;
	DDRD |= 1<<PIND5 | 1<<PIND4;

	TCCR1A |= 1<<COM1A1  | 1<<WGM11 | 1<<COM1B1;
	TCCR1B |= 1<<WGM12 | 1<<WGM13 | 1<<CS10;
	ICR1 = 255;
	int i = 0;

	int t=0;

	while(1)
	{
		/*if(t>=200)
		{
			t = 0;
			PORTB ^= 1<<PINB0;
		}*/

		OCR1B = 200;
		/*if(TCCR1B>200)
		{
			t++;
		}*/
		_delay_ms(1000);
		OCR1B = 50;
	}
}
