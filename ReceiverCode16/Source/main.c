#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

/*
 * OC0 - rightr
 * OC2 - rightf
 * OC1A - leftf
 * OC1B - leftr
 *
 *
 * OCR1A = leftf;
 * OCR1B = leftr;
 * OCR0 = rightf;
 * OCR2 = rightr;
 */

int x = 0, y = 0,prevx = 512, prevy = 512,buffer = 50,k=0,kill=0,buffer2 = 50,t=0,in=0,count=0,tx=0,ty=0,done=0,left = 0,right = 0,a=0,b=0;
char rec = '0';
int getData()
{

    while(!(UCSRA & (1<<RXC)));
    rec = (unsigned char)UDR;
    if(rec=='a' || rec=='b' || rec == '$' || rec == '#')
    {
            switch(rec)
            {
                case 'a':
                	count = 1;
                    break;
                case 'b':
                    //PORTB &= ~(1<<PINB4);
                	count = 2;
                    break;
                case '#':
                	count = 3;
                	break;
                default:
                	break;
            }
    }
    else
    {
    	if(count==1)
    		tx = (unsigned int)rec;
    	else if(count==2)
    		ty = (unsigned int)rec;
    }
    if(count==3)
    {
    	count = 0;
        return 1;
    }
    else
    {
        return 0;
    }
}

double map(int a, int b, int c, int d, int e)
{
  return (a-b)*1.0/((c-b)/(e-d)*1.0)*1.0 + d;
}
void main(void)
{
	int to = 255;
	//Variables init
	int leftr = 0,leftf = 0,rightr = 0,rightf = 0;
	int l = 0,r= 0;

	//DDR setup
	DDRD |= 1<<PORTD4 | 1<<PORTD5 | 1<<PORTD7;
	DDRB |= 1<<PORTB3 | 1<<PORTB0 | 1<<PORTB1 | 1<<PORTB2;

	//16 BIT TIMER
	TCCR1A |= 1<<WGM11 | 1<<COM1B1;
	TCCR1B |= 1<<WGM12 | 1<<WGM13 | 1<<CS10;
	ICR1 = to;
	//OCR1A - OCR1B

	//8BIT TIMER1
	TCCR0 |= 1<<WGM00 | 1<<WGM01 | 1<<COM01 | 1<<CS00;
	//OCR0

	//8BIT TIMER2
	//TCCR2 |= 1<<WGM21 | 1<<WGM20 | 1<<COM21 | 1<<CS20;
	//OCR2

	//UART
	UCSRA |= 1<<U2X;
	UCSRB |= 1<<RXEN;
	UCSRC |= 1<<UCSZ0 | 1<<UCSZ1;
	int ubr = 12;
	UBRRH = (unsigned char)(ubr>>8);
	UBRRL = (unsigned char)ubr;


	while(1)
	{
		int w = getData();
		if(w==1)
		{
			x = tx*4; y = ty*4;
			prevx = x;
			prevy = y;
			w = 0;
		}
		else if(w==0)
		{
			x = prevx;
			y = prevy;
		}
		if(x<=512+buffer2 && x>=512-buffer2 && y<=512+buffer2 && y>=512-buffer2)
		{
			leftf = leftr = rightf = rightr = 0; //both motors going 0
			left = right = 0;
			a = b = 1;
			PORTB &= ~(1<<PINB2);
		}
		else if(x<512+buffer2 && x>512-buffer2)
		{//Perfect Y Axis
			if(y>512+buffer2)
			{//Both the motors work in co-ordination backward
				right = left = map(y,512,1023,0,to);
				a = b = 0;
			}
			else if(y<512-buffer2)
			{//Both the motors work in co-ordination forward
				a = b = 1;
				left = right = map(y,0,511,to,0);
			}
		}
		else if(y<512+buffer2 && y>512-buffer2)
		{//Perfect X Axis
			if(x>512+buffer2)
			{//0deg
				a = 1;
				b = 0;
				left = map(x,512,1023,0,to);
				right = map(x,512,1023,0,to);
			}
			else if(x<512-buffer2)
			{//180deg
				a = 0;
				b = 1;
				left = map(x,0,511,to,0);
				right = map(x,0,511,to,0);
			}
		}
		else
		{
			PORTB |= 1<<PINB2;
			int refx,refy;
			if(y<512-buffer2)
			{
				if(x>512+buffer2)
				{
					refy = y;
					refx = 1023-refy;
					if(x<refx)
					{
						a = b = 1;
						left = map(y,0,511,to,0);
						right = map(x,512,refx,to,0);
					}
					else
					{
						a = 1;
						b = 0;
						refx = x;
						refy = 1023-refx;
						left = map(x,512,1023,0,to);
						right = map(y,refy,511,0,to);
					}
				}
				else if(x<512-buffer2)
				{
					refy = refx = y;
					if(x>refx)
					{
						a = b = 1;
						right = map(y,0,511,to,0);
						left = map(x,refx,511,0,to);
					}
					else
					{
						PORTB |= 1<<PINB2;
						a = 0;
						b = 1;
						refx = refy = x;
						right = map(x,0,511,to,0);
						left = map(y,refy,511,0,to);
				    }
				}
			}
			else
			{
				PORTB &= ~(1<<PINB2);
				if(x<512-buffer2)
				{
					refy = y;
					refx = 1023-refy;
					if(x>refx)
					{
						a = b = 0;
						left = map(y,512,1023,0,to);
						right = map(x,refx,511,0,to);
				    }
					else
					{
						a = 0;
						b = 1;
						refx = x;
						refy = 1023-refx;
						left = map(x,0,511,to,0);
						right = map(y,512,refy,to,0);
				    }
				}
				else
				{
					refx = refy = y;
					if(x>refx)
					{
						a = 1;
						b = 0;
						refx = refy = x;
						right = map(x,512,1023,0,to);
						left = map(y,512,refy,to,0);
					}
					else
					{
						a = b = 0;
						refx = refy = y;
						right = map(y,512,1023,0,to);
						left = map(x,512,refx,to,0);
					}
				}
			}
		}
		if(a==1)
			PORTB &= ~(1<<PINB0);
		else
			PORTB |= 1<<PINB0;
		if(b==1)
			PORTB &= ~(1<<PINB1);
		else
			PORTB |= 1<<PINB1;
		OCR0 = left;
		OCR1B = right;
	}
}


