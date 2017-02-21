#include <avr/io.h>
#include <util/delay.h>
#include<avr/iom32.h>

int main(void)
{
 DDRB |= 1 << PINB0;
 PORTB = 0b00000001;
}
