#include<avr/io.h>
void main(void)
{
	DDRB = 0b00000001;
	PORTB |= 0<<PINB0;
	//int count = 0;
	int t = 0;
	TCCR1B |= 1<<CS10;
	while(1)
	{
		if(TCNT1==50000)
		{
			if(t==0)
			{
				PORTB |= 1<<PINB0;
				TCNT1 = 0;
				t = 1;
			}
		}
		else if(TCNT1==35000)
		{
			if(t==1)
			{
				TCNT1 = 0;
				PORTB &= ~(1<<PINB0);
				t = 0;
			}
		}
	}
}
