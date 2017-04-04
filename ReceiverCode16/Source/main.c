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

int x = 0, y = 0,prevx = 512, prevy = 512,buffer = 50,k=0,kill=0,buffer2 = 50,t=0,in=0,tx=0,ty=0,left = 0,right = 0,a=0,b=0,resist=0,h=0,resist2=0;
char rec = '0';
int check[6];
int getData()
{
	TCNT2 = 0;
	resist = 0;
    while(!(UCSRA & (1<<RXC)))
    {
    	if(TCNT2==255)
    	{
    		resist++;
			if(resist>100)
			{
				kill = 1;
				resist = 0;
				break;
			}
    	}
    	//PORTB |= 1<<PINB0;
    }
   // PORTB &= ~(1<<PINB0);
    if(kill==0)
    {
		rec = (unsigned char)UDR;
		switch(rec)
		{
		case '$':
			if(check[0]==0)
				check[0] = 1;
			break;
		case 'a':
			if(check[0]==1)
			{
				check[1] = 1;
			}
			break;
		case 'b':
			if(check[2]==1)
			{
				check[3] = 1;
			}
			break;
		case '#':
			if(check[4]==1)
			{
				check[5] = 1;
			}
			break;
		default:
			if((check[0]==1 && check[1]==0) || (check[2]==1 && check[3]==0) || (check[4]==1 && check[5]==0)|| check[0]==0)
			{
				resist2++;
				if(resist2==20)
				{
					PORTB |= 1<<PINB0;
					for(int z=0;z<5;z++)
						check[z] = 0;
					tx = ty = 512;
					prevx = prevy = 512;
				}

			}
			if(check[1]==1 && check[3]==0)
			{
				tx = (unsigned int)rec;
				tx *= 4;
				check[2] = 1;
			}
			else if(check[3]==1)
			{
				ty = (unsigned int)rec;
				ty *= 4;
				check[4] = 1;
			}

			break;
		}
		int fi = 1;
		for(int z=0;z<5;z++)
		{
			if(!check[z])
			{
				fi = 0;
				break;
			}
		}
		if(fi == 1)
		{
			for(int z=0;z<5;z++)
				check[z] = 0;
			resist2 = 0;
			return 1;
		}
		else
		{
			if(check[5]==1)
			{
				for(int z=0;z<5;z++)
					check[z] = 0;
			}

			return 0;
		}
    }
    else
    {
    	tx = 512;
    	ty = 512;
    	return 1;
    }
}

double map(int a, int b, int c, int d, int e)
{
  return (a-b)*1.0/((c-b)/(e-d)*1.0)*1.0 + d;
}
void main(void)
{
	int to = 255;

	//DDR setup
	DDRD |= 1<<PORTD4 | 1<<PORTD5 | 1<<PORTD7 | 1<<PORTD3 | 1<<PORTD2;
	DDRB |= 1<<PORTB3 | 1<<PORTB0 | 1<<PORTB1 | 1<<PORTB2 | 1<<PORTB4;

	//16 BIT TIMER
	TCCR1A |= 1<<WGM11 | 1<<COM1B1;
	TCCR1B |= 1<<WGM12 | 1<<WGM13 | 1<<CS10;
	ICR1 = to;
	//OCR1A - OCR1B

	//8BIT TIMER1
	TCCR0 |= 1<<WGM00 | 1<<WGM01 | 1<<COM01 | 1<<CS00;
	//OCR0

	//8BIT TIMER2
	TCCR2 |= 1<<CS20 | 1<<CS21 | 1<<CS22;
	//OCR2

	//UART
	UCSRA |= 1<<U2X;
	UCSRB |= 1<<RXEN;
	UCSRC |= 1<<UCSZ0 | 1<<UCSZ1;
	int ubr = 12;
	UBRRH = (unsigned char)(ubr>>8);
	UBRRL = (unsigned char)ubr;

	for(int z=0;z<5;z++)
		check[z] = 0;

	while(1)
	{
		int w = getData();
		if(w==1)
		{
			if(tx==x && ty==y && !(tx<=512+buffer2 && tx>=512-buffer2 && ty<=512+buffer2 && ty>=512-buffer2))
			{
				h++;
			}
			else
				h = 0;
			if(h==500)
			{
				TCNT2 = 0;
				resist = 0;
				while(resist<100)
				{
					if(TCNT2==255)
						resist++;
				}
				tx = ty = 512;
				kill = 1;
				h = 0;
			}
			x = tx; y = ty;
			prevx = x;
			prevy = y;
			w = 0;
		}
		else if(w==0)
		{
			PORTB &= ~(1<<PINB0);
			x = prevx;
			y = prevy;
		}

		if(x<=512+buffer2 && x>=512-buffer2 && y<=512+buffer2 && y>=512-buffer2)
		{
			left = right = 0;
			a = b = 1;
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
				a = 0;
				b = 1;
				left = map(x,512,1023,0,to);
				right = map(x,512,1023,0,to);
			}
			else if(x<512-buffer2)
			{//180deg
				a = 1;
				b = 0;
				left = map(x,0,511,to,0);
				right = map(x,0,511,to,0);
			}
		}
		else
		{
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
						a = 0;
						b = 1;
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
						a = 1;
						b = 0;
						refx = refy = x;
						right = map(x,0,511,to,0);
						left = map(y,refy,511,0,to);
				    }
				}
			}
			else
			{
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
						a = 1;
						b = 0;
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
						a = 0;
						b = 1;
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
			PORTB |= 1<<PINB4;
		else
			PORTB &= ~(1<<PINB4);
		if(b==1)
			PORTD |= 1<<PIND2;
		else
			PORTD &= ~(1<<PIND2);
		OCR0 = right;
		OCR1B = left;
		if(kill==1)
		{
			kill = 0;
			TCNT2 = 0;
			resist = 0;
			while(resist<1000)
			{
				if(TCNT2==255)
					resist++;
			}
		}
	}
}


