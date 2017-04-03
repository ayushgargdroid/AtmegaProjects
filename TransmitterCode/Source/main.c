#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

/*
 * OC0 - rightr
 * OC2 - rightf
 * OC1A - leftf
 * OC1B - leftr
 *
 *
 * OCR1A = leftf;
 * OCR1B = leftr;
 * OCR0 = rightf;
 * OCR2 = rightr;
 */

int x = 127, y = 127,done=0,tx = 0,ty = 0;
void main(void)
{
	sei();
	int t = -1;
	//DDR setup
	DDRD |= 1<<PORTD4 | 1<<PORTD5 | 1<<PORTD7;
	DDRB |= 1<<PORTB3 | 1<<PORTB0 | 1<<PORTB1 | 1<<PORTB2;

	//ADC SETUP
	ADMUX = 0x40;
	ADCSRA |= 1<<ADEN | 1<<ADIE | 1<<ADPS2 | 1<<ADSC;

	//UART
	UCSRA |= 1<<U2X;
	UCSRB |= 1<<TXEN;
	UCSRC |= 1<<UCSZ0 | 1<<UCSZ1;
	int ubr = 12;
	UBRRH = (unsigned char)(ubr>>8);
	UBRRL = (unsigned char)ubr;

	//16 BIT TIMER
	//OCR1A - OCR1B
	TCCR1A |= 1<<COM1B1 | 1<<WGM11;
	TCCR1B |= 1<<CS10 | 1<<WGM13 | 1<<WGM12;
	ICR1 = 255;

	//8BIT TIMER1
	TCCR0 |= 1<<WGM00 | 1<<WGM01 | 1<<COM01 | 1<<CS00;
	//OCR0

	//8BIT TIMER2
	//TCCR2 |= 1<<WGM21 | 1<<WGM20 | 1<<COM21 | 1<<CS20;
	//OCR2
	int i = 0;

	while(1)
	{
		/*UDR = '$';
		_delay_ms(100);
		UDR = 'a';
		_delay_ms(100);
		UDR = 127&0xFF;
		_delay_ms(100);
		UDR = 'b';
		_delay_ms(100);
		UDR = 0&0xFF;
		_delay_ms(100);
		UDR = '#';
		_delay_ms(100);*/
		if(i>5000)
		{
			while (! (UCSRA & (1 << UDRE)) );
			PORTB |= 1<<PINB2;
			switch(t)
			{
			case -1:
				UDR = '$';
				_delay_ms(10);
				break;
			case 0:
				UDR = 'a';
				_delay_ms(10);
				break;
			case 1:
				UDR = (x & 0xFF);
				_delay_ms(10);
				break;
			case 2:
				UDR = 'b';
				_delay_ms(10);
				break;
			case 3:
				UDR = (y & 0xFF);
				_delay_ms(10);
				break;
			case 4:
				UDR = '#';
				_delay_ms(10);
				t = -2;
				break;
			}
			t++;
			OCR1B = x;
			OCR0 = y;
		}
		else
		{
			i++;
		}

	}

}
ISR(ADC_vect)
{
	uint8_t low = ADCL;
	uint16_t t = ADCH << 8 | low;
	switch(ADMUX)
	{
	case 0x40:
		tx = t;
		ADMUX = 0x41;
		break;
	case 0x41:
		ty = t;
		ADMUX = 0x40;
		done = 1;
		break;
	}
	if(done==1)
	{
		x = tx/4;
		y = ty/4;
		done = 0;
		switch(x)
		{
		case 35:
			x = 34;
			break;
		case 36:
			x = 37;
			break;
		case 97:
			x = 96;
			break;
		case 98:
			x = 99;
			break;
		}
		switch(y)
		{
		case 35:
			y = 34;
			break;
		case 36:
			y = 37;
			break;
		case 97:
			y = 96;
			break;
		case 98:
			y = 99;
			break;
		}
	}
	ADCSRA |= 1<<ADSC;

}
