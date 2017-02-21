#include<avr/io.h>
#include<util/delay.h>

int ex = 0;


void initMaster(void)
{
	PORTB |= 1<<PINB1;
	TWBR = 0x02;
	TWAR = 0b11111000;
}

void startMaster(void)
{
	TWCR |= 1<<TWSTA | 1<<TWINT | 1<<TWEN;
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != 0x08)
	{
		ex = 1;

	}
}

void addressMaster(void)
{

	TWDR = 0xD6;
	TWCR |= 1<<TWEN | 1<<TWINT;
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) == 0x18)
	{
		ex = 1;
		PORTB |= 1<<PINB0;
						_delay_ms(100);
						PORTB &= ~(1<<PINB0);
						_delay_ms(100);
	}
}

void dataMaster(void)
{
	TWDR = 0xFF;
	TWCR &= ~(1<<TWSTA);
	TWCR |= (1<<TWEN) | (1<<TWINT);
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != 0x28)
	{
		ex = 1;
	}
}

void stopMaster(void)
{
	TWCR |= 1<<TWINT | 1<<TWEN | 1<<TWSTO;
}






void initSlave(void)
{
	TWAR = 0x0E;
}

void addressSlave(void)
{
	TWCR |= 1<<TWEN | 1<<TWEA | 1<<TWINT;
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != 0x60)
	{
		ex = 1;
	}
}

void dataSlave(void)
{
	TWCR |= 1<<TWEN | 1<<TWEA | 1<<TWINT;
	while(!(TWCR & (1<<TWINT)));

	if((TWSR & 0xF8) != 0x80)
	{
		ex = 1;
	}
	if(TWDR==0xFF)
		PORTB ^= 1<<PINB0;
}

void stopSlave(void)
{
	TWCR |= 1<<TWEN | 1<<TWEA | 1<<TWINT;
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != 0xA0)
	{
		ex = 1;

	}
	if(ex==0)
	{
		PORTB |= 1<<PINB2;
		_delay_ms(100);
		PORTB &= ~(1<<PINB2);
	}
}

void main(void)
{
	DDRB |= 1<<PINB0 | 1<<PINB2;
	initMaster();

	//TWI
	TWCR |= 1<<TWEN;

	while(1)
	{
		if(bit_is_clear(PINB,1))
		{
			_delay_ms(100);
			if(bit_is_clear(PINB,1))
			{
				//PORTB ^= 1<<PINB0;
				startMaster();
				addressMaster();
				dataMaster();
				stopMaster();
			}
		}
		/*while(ex==0)
		{
			initSlave();
			addressSlave();
			dataSlave();
			stopSlave();
		}*/

	}
}
