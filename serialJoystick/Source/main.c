#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

unsigned char rec = '0',ded = '0',ted='0';
int in=0,count=3,leftf=0,leftr=0,rightr=0,rightf=0,t=0;

int powCust(int x,int y)
{
	int m=1;
	for(int i=0;i<y;i++)
		m*=x;
	return m;
}
void main(void)
{
	sei();
	DDRB |= 1<<PINB0 | 1<<PINB1 | 1<<PINB2 | 1<<PORTB3;
	DDRD |= 1<<PORTD4 | 1<<PORTD5 | 1<<PORTD7;
	DDRB |= 1<<PORTB3;

	//16 BIT TIMER
	TCCR1A |= 1<<COM1A1  | 1<<WGM11 | 1<<COM1B1;
	TCCR1B |= 1<<WGM12 | 1<<WGM13 | 1<<CS10;
	ICR1 = 255;
	//OCR1A - OCR1B

	//8BIT TIMER1
	TCCR0 |= 1<<WGM00 | 1<<WGM01 | 1<<COM01 | 1<<CS00;
	//OCR0

	//8BIT TIMER2
	TCCR2 |= 1<<WGM21 | 1<<WGM20 | 1<<COM21 | 1<<CS20;
	//OCR2

	//USART COMMUNICATION
	UCSRA |= 1<<U2X;
	UCSRB |= 1<<RXCIE | 1<<RXEN | 1<<TXEN;
	UCSRC |= 1<<UCSZ0 | 1<<UCSZ1;
	int ubr = 12;
	UBRRH = (unsigned char)(ubr>>8);
	UBRRL = (unsigned char)ubr;

	while(1)
	{

		OCR1A = leftf;
		OCR1B = leftr;
		OCR0 = rightf;
		OCR2 = rightr;

	}

}

ISR(USART_RXC_vect)
{
	rec = (unsigned char)UDR;
	//ted = rec;
	t = rec - '0';
	if(t>=0 && t<=9)
	{
		ded=rec;
		in = in + (t*powCust(10,count));
		count--;
		while (! (UCSRA & (1 << UDRE)) );
				UDR = (unsigned char)ded;
	}
	else
	{
		if(count==0)
		{
			in -= 100;
			int t1 = in/1000;
			switch(t1)
			{
			case 'a':
				leftf = in%1000;
				PORTB &= ~(1<<PINB4);
				OCR0 = leftf;
				break;
			case 'b':
				leftr = in%1000;
				PORTB |= (1<<PINB4);
				OCRO = leftr;
				break;
			case 'c':
				rightf = in%1000;
				PORTD &= ~(1<<PIND4);
				OCR1B = rightf;
				break;
			case 'd':
				rightr = in%1000;
				PORTD |= 1<<PIND4;
				OCR1B = rightl;
				break;
			}
		}
		count = 3;
		in = 0;
	}
	
}
