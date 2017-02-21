#include<avr/io.h>

void main(void)
{
	DDRB = 0b00000001;
	PORTB = 0b00000010;
	int pressed = 0,c=0,c1=0;
	while(1)
	{
		if(bit_is_clear(PINB,1))
		{
			c++;
			//PORTB = 0b00000011;
			if(c>400)
			{
				if(pressed==0)
				{
					pressed = 1;
					PORTB ^= 1<<PINB0;
				}
				c = 0;
			}
		}
		else
		{
			c1++;
			if(c1>200)
			{
				pressed = 0;
				c1 = 0;
			}
		}
	}
}
