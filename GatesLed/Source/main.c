#include<avr/io.h>
#include<util/delay.h>

void main(void)
{
	DDRB |= 1<<PINB0;
	PORTB = 0b00001110;
	int a,b,ex=0;
	int count=0,count1=0,count3=0,count4=0;
	int pressed=0,c[2];
	c[0]=c[1]=0;
	while(1)
	{
		if(bit_is_clear(PINB,3))
		{
			c[0]++;
			if(c[0]>400)
			{
				if(pressed==0)
				{
					ex = ex==0?1:0;
					pressed = 1;
				}
				c[0]=0;
			}
		}
		else
		{
			c[1]++;
			if(c[1]>400)
			{
				pressed = 0;
				c[1]=0;
			}
		}
		if(bit_is_clear(PINB,1))
		{
			count++;
			if(count>400)
			{
				a = 1;
				count = 0;
			}
		}
		else
		{
			count1++;
			if(count1>400)
			{
				a = 0;
				count1 = 0;
			}
		}
		if(bit_is_clear(PINB,2))
		{
			count3++;
			if(count3>400)
			{
				b = 1;
				count3 = 0;
			}
		}
		else
		{
			count4++;
			if(count4>400)
			{
				b = 0;
				count4 = 0;
			}
		}
		if(ex==0)
		{
			if(a&&b)
			{
				PORTB |= 1<<PINB0;
			}
			else
			{
				PORTB &= ~(1<<PINB0);
			}
		}
		else
		{
			if(a||b)
			{
				PORTB |= 1<<PINB0;
			}
			else
			{
				PORTB &= ~(1<<PINB0);
			}
		}
	}
}
