#include<avr/io.h>
#include<util/delay.h>

int main(void)
{
	DDRB = 0b00000001;
	int pressed = 0;
	int count = 0,i;
	int buton,butoff;
	PORTB = 0b00000010;
	while(1)
	{
		if(count==7)
		{
			count = 0;
		}
		if(bit_is_clear(PINB,1))
		{
			buton++;
			if(buton>200)
			{
				if(pressed==0)
				{
					pressed = 1;
					count++;
					for(i = 0;i<count*2;i++)
					{
						PORTB ^= 1<<PINB0;
						_delay_ms(300);
					}
				}
				buton = 0;
			}
		}
		else
		{
			pressed = 0;
			PORTB ^= 1<<PINB0;
		}
	}

}
