#include<avr/io.h>
#include<util/delay.h>

void masterInit(void)
{
	DDRC |= 1<<PINC0 | 1<<PINC1;
	TWCR |= 1<<TWEN;
	PORTB |= 1<<PINB1;
	TWSR = 0x00;
	TWBR = 0x02;
	TWAR = 0b11111000;
}

int transmitData(void)
{
	TWCR |= 1<<TWSTA | 1<<TWINT | 1<<TWEN;

	//wait for start condition to occur
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != 0x08)
		return 1;
	TWCR &= ~(1<<TWSTA);


	//Address Transmit
	TWDR = 0x3C;
	TWCR |= 1<<TWEN | 1<<TWINT;
	while(!(TWCR & (1<<TWINT)));

	if((TWAR == 0x38))
	{
		PORTB |= 1<<PINB2;
			_delay_ms(100);
			PORTB &= ~(1<<PINB2);
	}
	if((TWSR & 0xF8) != 0x18)
		return 1;


	//Data Transmit
	TWDR = 0x28;
	TWCR |= 1<<TWEN | 1<<TWINT;
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != 0x28)
		return 1;
	//Stop Transmit
	TWCR |= 1<<TWINT | 1<<TWEN | 1<<TWSTO;

	/*PORTB |= 1<<PINB2;
	_delay_ms(100);
	PORTB &= ~(1<<PINB2);*/
	return 0;
}

void main(void)
{
	DDRB |= 1<<PINB0 | 1<<PINB2;

	masterInit();

	while(1)
	{
		if(bit_is_clear(PINB,1))
		{
			_delay_ms(100);
			if(bit_is_clear(PINB,1))
			{
				PORTB ^= 1<<PINB0;
				if(transmitData()==1)
				{
					break;
				}
			}
		}
	}

}

