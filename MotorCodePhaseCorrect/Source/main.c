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

int x = 0, y = 0,prevx = 512, prevy = 512,buffer = 50,k=0,kill=0,buffer2 = 20;

double map(int a, int b, int c, int d, int e)
{
  return (a-b)*1.0/((c-b)/(e-d)*1.0)*1.0 + d;
}
void main(void)
{
	sei();
	int to = 255;
	//Variables init
	int leftr = 0,leftf = 0,rightr = 0,rightf = 0,tx = 0,ty = 0;
	int l = 0,r= 0;

	//DDR setup
	DDRD |= 1<<PORTD4 | 1<<PORTD5 | 1<<PORTD7;
	DDRB |= 1<<PORTB3 | 1<<PORTB0 | 1<<PORTB1;

	//ADC SETUP
	ADMUX = 0x40;
	ADCSRA |= 1<<ADEN | 1<<ADIE | 1<<ADPS2 | 1<<ADSC;

	//16 BIT TIMER
	TCCR1A |= 1<<COM1A1  | 1<<COM1B1;
	TCCR1B |= 1<<WGM13 | 1<<CS10;
	ICR1 = 127;
	//OCR1A - OCR1B

	//8BIT TIMER1
	//TCCR0 |= 1<<WGM00 | 1<<WGM01 | 1<<COM01 | 1<<CS00;
	//OCR0

	//8BIT TIMER2
	//TCCR2 |= 1<<WGM21 | 1<<WGM20 | 1<<COM21 | 1<<CS20;
	//OCR2

	while(1)
	{
		if(!(x<=512+buffer2 && x>=512-buffer2 && y<=512+buffer2 && y>=512-buffer2))
		{
			if(TCNT1==0)
			{
				tx = x;
				ty = y;
			}
			else if(TCNT1>=200)
			{
				k++;
			}
			/*if(k>=4000)
			{
				if((tx==x) || (ty==y))
				{
					k = 0;
					kill = 1;
					ADCSRA &= ~(1<<ADSC);
					leftr = leftf = rightr = rightf = 0;
					OCR1A = OCR1B = OCR0 = OCR2 = 0;
					PORTB |= 1<<PINB0;
					while(!(leftf==0 && leftr==0 && rightf==0 &&rightr==0))
					{
						if(leftf==0)
						{
							leftr -= 50;
						}
						else if(leftr==0)
						{
							leftf -= 50;
						}
						if(rightf==0)
						{
							rightr -= 50;
						}
						else if(rightr==0)
						{
							rightf -= 50;
						}
						leftf = (leftf<0)?0:leftf;
						leftr = (leftr<0)?0:leftr;
						rightf = (rightf<0)?0:rightf;
						rightr = (rightr<0)?0:rightr;
					}
				}
				else
					k = 0;
			}*/

		}
		if(x<=512+buffer2 && x>=512-buffer2 && y<=512+buffer2 && y>=512-buffer2)
		{
			if(kill!=1)
				leftf = leftr = rightf = rightr = 0; //both motors going 0
		}
		else if(x<512+buffer2 && x>512-buffer2)
		{//Perfect Y Axis
			if(y>512+buffer2)
			{//Both the motors work in co-ordination backward
		      rightf = leftr = map(y,512,1023,0,to);
		      leftf = rightr = 0;
		    }
		    else if(y<512-buffer2)
		    {//Both the motors work in co-ordination forward
		      rightf = leftr = 0;
		      leftf = rightr = map(y,0,511,to,0);
		    }
		}
		else if(y<512+buffer2 && y>512-buffer2)
		{//Perfect X Axis
			if(x>512+buffer2)
		    {//0deg
		      leftf = map(x,512,1023,0,to);leftr = 0;
		      rightf = map(x,512,1023,0,to);rightr = 0;
		    }
		    else if(x<512-buffer2)
		    {//180deg
		      leftf = 0;leftr = map(x,0,511,to,0);
		      rightf = 0;rightr = map(x,0,511,to,0);
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
		          leftr = 0;
		          leftf = map(y,0,511,to,0);
		          rightf = 0;
		          rightr = map(x,512,refx,to,0);
		        }
		        else
		        {
		          refx = x;
		          refy = 1023-refx;
		          leftr = 0;
		          leftf = map(x,512,1023,0,to);
		          rightr = 0;
		          rightf = map(y,refy,511,0,to);
		        }
		      }
		      else if(x<512-buffer2)
		      {
		        refy = refx = y;
		        if(x>refx)
		        {
		          rightf = 0;
		          rightr = map(y,0,511,to,0);
		          leftr = 0;
		          leftf = map(x,refx,511,0,to);
		        }
		        else
		        {
		          refx = refy = x;
		          rightf = 0;
		          rightr = map(x,0,511,to,0);
		          leftf = 0;
		          leftr = map(y,refy,511,0,to);
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
		          leftf = 0;
		          leftr = map(y,512,1023,0,to);
		          rightr = 0;
		          rightf = map(x,refx,511,0,to);
		        }
		        else
		        {
		          refx = x;
		          refy = 1023-refx;
		          leftf = 0;
		          leftr = map(x,0,511,to,0);
		          rightf = 0;
		          rightr = map(y,512,refy,to,0);
		        }
		      }
		      else
		      {
		        refx = refy = y;
		        if(x>refx)
		        {
		          refx = refy = x;
		          rightr = 0;
		          rightf = map(x,512,1023,0,to);
		          leftr = 0;
		          leftf = map(y,512,refy,to,0);
		        }
		        else
		        {
		          refx = refy = y;
		          rightr = 0;
		          rightf = map(y,512,1023,0,to);
		          leftf = 0;
		          leftr = map(x,512,refx,to,0);
		        }
		      }
		    }
		}
		l = leftr==0 ? 0:1;
		r = rightf==0 ? 0:1;
		if(l==0)
		{
			PORTB &= ~(1<<PINB0);
			OCR1A = 127 - (to-leftf)/2.0;
		}
		else
		{
			PORTB |= 1<<PINB0;
			OCR1A = 127 - (to-leftr)/2.0;
		}
		if(r==0)
		{
			PORTB &= ~(1<<PINB1);
			OCR1B = 127 - (to-rightr)/2.0;
		}
		else
		{
			PORTB |= 1<<PINB1;
			OCR1B = 127 - (to-rightf)/2.0;
		}
		if(kill==1)break;
		/*OCR1A = leftf;
		OCR1B = leftr;
		OCR0 = rightf;
		OCR2 = rightr;*/
		prevx = x;
		prevy = y;
	}

}
ISR(ADC_vect)
{
	uint8_t low = ADCL;
	uint16_t t = ADCH << 8 | low;
	switch(ADMUX)
	{
	case 0x40:
		x = t;
		ADMUX = 0x41;
		break;
	case 0x41:
		y = t;
		ADMUX = 0x40;
		break;
	}
	if(x-prevx>buffer)
	{
	  x = prevx+buffer;
	}
	else if(x-prevx<-buffer)
	{
	  x = prevx-buffer;
	}
	if(y-prevy>buffer)
	{
	  y = prevy+buffer;
	}
	else if(y-prevy<-buffer)
	{
	  y = prevy-buffer;
	}
	ADCSRA |= 1<<ADSC;

}
