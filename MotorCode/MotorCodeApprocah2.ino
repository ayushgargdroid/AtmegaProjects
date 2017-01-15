#include<math.h>
int buffer,buffer2;
int x,y,prevx,prevy;
int leftf,leftr,rightf,rightr;
void setup()
{
  Serial.begin(9600);
  buffer = 50;
  buffer2 = 20;
  x = y = leftr = leftf = rightr = rightf = 0;
  pinMode(A0,INPUT);//x
  pinMode(A1,INPUT);//y
}
void loop()
{
  x = analogRead(A0);
  y = analogRead(A1);
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
  if(x<=512+buffer2 && x>=512-buffer2 && y<=512+buffer2 && y>=512-buffer2)
  {
    leftf = leftr = rightf = rightr = 0; //both motors going 0
  }
  else if(x<512+buffer2 && x>512-buffer2)
  {//Perfect Y Axis
    if(y>512+buffer2)
    {//Both the motors work in co-ordination backward
      rightf = leftr = map(y,512,1023,0,255);
      leftf = rightr = 0; 
    }
    else if(y<512-buffer2)
    {//Both the motors work in co-ordination forward
      rightf = leftr = 0;
      leftf = rightr = map(y,0,512,255,0);
    }
  }
  else if(y<512+buffer2 && y>512-buffer2)
  {//Perfect X Axis
    if(x>512+buffer2)
    {//0deg
      leftf = map(x,512,1023,0,255);leftr = 0;
      rightf = map(x,512,1023,0,255);rightr = 0;
    }
    else if(x<512-buffer2)
    {//180deg
      leftf = 0;leftr = map(x,0,512,255,0);
      rightf = 0;rightr = map(x,0,512,255,0);
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
          leftf = map(y,0,512,255,0);
          rightf = 0;
          rightr = map(x,512,refx,255,0);
        }
        else
        {
          refx = x;
          refy = 1023-refx;
          leftr = 0;
          leftf = map(x,512,1023,0,255);
          rightr = 0;
          rightf = map(y,refy,512,0,255);
        }
      }
      else if(x<512-buffer2)
      {
        refy = refx = y;
        if(x>refx)
        {
          rightf = 0;
          rightr = map(y,0,512,255,0);
          leftr = 0;
          leftf = map(x,refx,512,0,255);
        }
        else
        {
          refx = refy = x;
          rightf = 0;
          rightr = map(x,0,512,255,0);
          leftf = 0;
          leftr = map(y,refy,512,0,255);
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
          leftr = map(y,512,1023,0,255);
          rightr = 0;
          rightf = map(x,refx,512,0,255);
        }
        else
        {
          refx = x;
          refy = 1023-refx;
          leftf = 0;
          leftr = map(x,0,512,255,0);
          rightf = 0;
          rightr = map(y,512,refy,255,0);
        }
      }
      else
      {
        refx = refy = y;
        if(x>refx)
        {
          refx = refy = x;
          rightr = 0;
          rightf = map(x,512,1023,0,255);
          leftr = 0;
          leftf = map(y,512,refy,255,0);
        }
        else
        {
          refx = refy = y;
          rightr = 0;
          rightf = map(y,512,1023,0,255);
          leftf = 0;
          leftr = map(x,512,refx,255,0);
        }
      }
    }
  }
  analogWrite(11,rightf);
  analogWrite(10,rightr);
  analogWrite(9,leftr);
  analogWrite(6,leftf);
  prevy = y;
  prevx = x;
}
  
