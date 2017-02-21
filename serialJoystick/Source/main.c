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
	DDRB |= 1<<PINB0 | 1<<PINB1 | 1<<PINB2;
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
		count = 3;
		int t1 = in/1000;
		switch(t1)
		{
		case 0:
			leftf = in%1000;
			break;
		case 1:
			leftr = in%1000;
			break;
		case 2:
			rightf = in%1000;
			break;
		case 3:
			rightr = in%1000;
			break;
		}
		in = 0;
	}
	/*if(rec<='9' && rec>='0')
	{
		if(count==0)
		{
			ded=rec;
			ted=rec;
		}
		int t = (rec - '0');
		in = in + (t*pow(10,count--));
		//PORTB ^= 1<<PINB0;
		//_delay_ms(100);
	}
	else
	{
		ded=ted;
	}
	else
	{
		PORTB |= 1<<PINB2;
		int t = rec/1000;
		switch(t)
		{
		case 0:
			leftf = t%1000;
			break;
		case 1:
			leftr = t%1000;
			break;
		case 2:
			rightf = t%1000;
			break;
		case 3:
			rightr = t%1000;
			break;
		}
		if(in==1255)PORTB |= 1<<PINB0;
		count = 3;
		in = 0;
	}*/
}
