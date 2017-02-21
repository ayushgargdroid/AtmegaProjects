#include<avr/io.h>
#include<util/delay.h>

int main(void)
{
	DDRC = 0b11111111;
	DDRD = 0b11111111;
	PORTB &= ~(1<<PINB0);
	PORTB &= ~(1<<PINB1);
	int l[8],r[8];
	int i=0,pressedl,pressedr,countonl,countoffl,countonr,countoffr,posl=-1,posr=-1;
	for(i=0;i<8;i++)
	{
		l[i] = 0;
		r[i] = 0;
	}
	while(1)
	{
		if(posl==7)
		{
			for(i=0;i<20;i++)
			{
				PORTD ^= 0b11111111;
				_delay_ms(200);
			}
			break;
		}
		else if(posr==7)
		{
			for(i=0;i<20;i++)
			{
				PORTC ^=0b11111111;
				_delay_ms(200);
			}
			break;
		}
		if(bit_is_clear(PINB,0))
		{
			countonl++;
			if(countonl>=400 && pressedl==0)
			{
				pressedl = 1;
				countonl = 0;
				l[++posl] = 1;
				PORTC |= 1<<posl;
			}
		}
		else
		{
			countoffl++;
			if(countoffl>=400)
			{
				pressedl = 0;
				countoffl = 0;
				countonl = 0;
			}
		}
		if(bit_is_clear(PINB,1))
		{
			countonr++;
			if(countonr>=400 && pressedr==0)
			{
				pressedr = 1;
				countonr = 0;
				l[++posr] = 1;
				PORTD |= 1<<posr;
			}
		}
		else
		{
			countoffr++;
			if(countoffr>=400)
			{
				pressedr = 0;
				countoffr = 0;
				countonr = 0;
			}
		}
	}
}
