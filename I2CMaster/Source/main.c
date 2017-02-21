#include<avr/io.h>
#include<util/delay.h>

int ex = 0;
uint8_t k = 0;

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

void addressMaster(unsigned char add)
{

	TWDR = add;
	TWCR |= 1<<TWEN | 1<<TWINT;
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != 0x18)
	{
		ex = 1;
	}
}

void dataMaster(unsigned char data)
{
	TWDR = data;
	TWCR &= ~(1<<TWSTA);
	TWCR |= (1<<TWEN) | (1<<TWINT);
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != 0x28)
	{
		ex = 1;
	}
}

void receiveMaster(void)
{
	TWCR &= ~(1<<TWSTA);
	TWCR |= 1<<TWEN | 1<<TWINT;
	while(!(TWCR & (1<<TWINT)));
	unsigned char i = TWDR;
	if((TWSR & 0xF8) == 0x58)
	{
		ex = 1;
		/*PORTB |= 1<<PINB0;
		_delay_ms(100);
		PORTB &= ~(1<<PINB0);
		_delay_ms(100);*/
	}
	k = i;
}

void stopMaster(void)
{
	TWCR |= 1<<TWINT | 1<<TWEN | 1<<TWSTO;
}


void main(void)
{
	DDRB |= 1<<PINB0 | 1<<PINB2 | 1<<PINB3;
	initMaster();
	TCCR0 = WGM01 | 1<<WGM00 | 1<<COM01 | 1<<CS00;

	//TWI
	TWCR |= 1<<TWEN;

	while(1)
	{
		//if(bit_is_clear(PINB,1))
		{
			//_delay_ms(100);
			//if(bit_is_clear(PINB,1))
			{
				//PORTB ^= 1<<PINB0;
				startMaster();
				addressMaster(0xD6);
				dataMaster(0x28);
				startMaster();
				addressMaster(0xD7);
				receiveMaster();
				OCR0 = k;
				stopMaster();
			}
		}

	}
}
