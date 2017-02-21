#include<avr/io.h>
#include<util/delay.h>

void masterInit(void)
{
	DDRB |= 1<<PINB5 | 1<<PINB7;
	PORTB |= 1<<PINB1 | 1<<PINB4;
	SPCR |= 1<<SPE | 1<<MSTR;
}
void slaveInit(void)
{
	DDRB |= 1<<PINB6;
	SPCR |= 1<<SPE;
}
void transmitOn(void)
{
	//PORTB &= ~(1<<PINB4);
	PORTB |= 1<<PINB2;
	SPDR = (unsigned char)'A';
	while(!(SPSR&(1<<SPIF)));
	_delay_ms(100);
	PORTB &= ~(1<<PINB2);
	//PORTB |= 1<<PINB4;
}
void receive(void)
{
	PORTB |= 1<<PINB2;
	while(!(SPSR&(1<<SPIF)));
	char t = (unsigned char)SPDR;
	if(t=='A')
		PORTB ^= 1<<PINB0;
	_delay_ms(100);
	PORTB &= ~(1<<PINB2);
}
void main(void)
{
	DDRB |= 1<<PINB0 | 1<<PINB2;
	//masterInit();
	slaveInit();

	while(1)
	{
		/*if(bit_is_clear(PINB,1))
		{
			_delay_ms(100);
			if(bit_is_clear(PINB,1))
			{
				PORTB ^= 1<<PINB0;
				transmitOn();
			}
		}*/
		receive();
	}

}

