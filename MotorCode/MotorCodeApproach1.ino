#include<math.h>
int buffer,buffer2;
int x,y,centerx,centery,prevx,prevy,prevangle,prevQ,tr,tl,prevtr,prevtl,buffer3;
int leftf,leftr,rightf,rightr;
void setup()
{
  Serial.begin(9600);
  x = y = tr = tl = prevQ = prevtl = prevtr = 0;
  prevangle =  0;
  prevx = prevy = 512;
  buffer = 50;
  buffer2 = 2;
  buffer3 = 20;
  centerx = centery = prevx = prevy = 512;
  pinMode(A0,INPUT);//x
  pinMode(A1,INPUT);//y
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
}
int getAngle(int x,int y)
{
  double m1 = (y-512.0)/(x-512.0);
  double m2 = (512.0-512.0)/(1023.0-0.0);  
  int tangle =(int)(atan((m2-m1)/(1+m1*m2))*57.3);
  if(x>centerx-buffer && x<centerx+buffer)
  {
    if(y>=512) tangle = 270;
    else tangle = 90;
  }
  else if(x < 512) tangle+=180;
  else if(y>512) tangle+=360;
  if(tangle==360) tangle = 0;
  if(x>centerx-buffer && x<centerx+buffer && y>centery-buffer && y<centery+buffer)
   tangle = 0;
  return tangle;
}
void loop()
{
  int currQ;
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
  int angle = getAngle(x,y);
  if(prevangle>=315-buffer2 && prevangle<=315+buffer2 && (abs(prevx-x)==buffer) &&(abs(prevy-y)==buffer))
  {
    y=x;
    angle = 315;
  }
  else if(prevangle>=225-buffer2 && prevangle<=225+buffer2 && (abs(prevx-x)==buffer) &&(abs(prevy-y)==buffer))
  {
    y=1023 - x;
    angle = 225;
  }
  else if(prevangle>=135-buffer2 && prevangle<=135+buffer2 && (abs(prevx-x)==buffer) &&(abs(prevy-y)==buffer))
  {
    y=x;
    angle = 135;
  }
  else if(prevangle>=45-buffer2 && prevangle<=45+buffer2 && (abs(prevx-x)==buffer) &&(abs(prevy-y)==buffer))
  {
    y=1023 - x;
    angle = 45;
  }
  int t = (int)sqrt(pow((x-512),2) + pow((y-512),2));//distance formula
  t = constrain(t,0,512);//constraining the value to 512
  t = (int)map(t,0,512,0,255);//Calculating the value for both the motors w.r.t. distance formula
  if(x<=512+buffer3 && x>=512-buffer3 && y<=512+buffer3 && y>=512-buffer3)
  {
    t =  0; //Power going to 0
    leftf = leftr = rightf = rightr = 0; //both motors going 0
    angle = 0;
  }
  else if(x<512+buffer3 && x>512-buffer3)
  {//Perfect Y Axis
    if(y>512+buffer3)
    {//Both the motors work in co-ordination forward
      rightf = leftr = t;
      leftf = rightr = 0; 
      currQ = 1;
    }
    else if(y<512-buffer3)
    {//Both the motors work in co-ordination backward
      rightf = leftr = 0;
      leftf = rightr = t;
      currQ = 3;
    }
  }
  else if(y<512+buffer3 && y>512-buffer3)
  {//Perfect X Axis
    if(x>512+buffer3)
    {//0deg
      leftf = t;leftr = 0;
      rightf = t;rightr = 0;
      currQ = 1;
      Serial.print(" yo");
    }
    else if(x<512-buffer3)
    {//180deg
      leftf = 0;leftr = t;
      rightf = 0;rightr = t;
      currQ = 2;
    }
  }
  else
  {
    if(angle<90)
    {
      leftf = t;
      leftr = 0; //Left motor is always clockwise in this region
      if(angle<45-buffer2)
      {//1st octant
        rightr = 0;
        rightf = map(angle,0,45,255,0);
      }
      else
      {//2nd octant
        angle = constrain(angle,45,90);
        rightf = 0;
        rightr = map(angle,90,45,255,0);
      }
    }
    else if(angle<180)
    {
      rightf = 0;
      rightr = t;
      if(angle<135+buffer2)
      {//3rd octant
        angle = constrain(angle,90,135);
        leftr = 0;
        leftf = map(angle,90,135,255,0);
      }
      else
      {//4th octant
        leftf = 0;
        leftr = map(angle,135,180,0,255);
      }
    }
    else if(angle<270)
    {
      leftf = 0;
      leftr = t;
      if(angle<225+buffer2)
      {//5th octant
        angle = constrain(angle,180,225);
        rightf = 0;
        rightr = map(angle,180,225,255,0);
      }
      else
      {//6th octant
        rightr = 0;
        rightf = map(angle,225,270,0,255);
      }
    }
    else
    {
      rightr = 0;
      rightf = t;
      if(angle<315+buffer2)
      {//7th octant
        angle = constrain(angle,270,315);
        leftf = 0;
        leftr = map(angle,270,315,255,0);
      }
      else
      {
        leftr = 0;
        leftf = map(angle,315,359,0,255);
      }
    }
  }
  prevx = x;
  prevy = y;
  prevangle = angle;
  analogWrite(11,rightf);
  analogWrite(10,rightr);
  analogWrite(9,leftr);
  analogWrite(6,leftf);
  Serial.print("x : ");
  Serial.print(x);
  Serial.print(" y : ");
  Serial.print(y);
  Serial.print(" angle : ");
  Serial.println(angle);
  /*Serial.print("Left front : ");
  Serial.print(leftf);
  Serial.print(" Left rear : ");
  Serial.print(leftr);
  Serial.print(" Right front : ");
  Serial.print(rightf);
  Serial.print(" Right rear : ");
  Serial.println(rightr);*/
}
