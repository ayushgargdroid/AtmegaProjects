import org.gamecontrolplus.gui.*;
import org.gamecontrolplus.*;
import net.java.games.input.*;
import processing.serial.*;
import cc.arduino.*;

Arduino arduino;
ControlIO control;
Configuration config;
ControlDevice gpad;

int x,y,rotr,rotl,buffer,angle,prevx,prevy,powr,powl,currQ,prevQ,prevAngle;
boolean mode = false;
//int ledfr = 5, ledfl = 3,ledbl = 9,ledbr = 6;
int enl = 3,enr = 9,l1 = 10,l2 = 11,r1 = 12,r2 = 13;

public void setup()
{
  x = y = rotr = rotl = angle = prevx = prevy = powr = powl = prevQ = currQ = prevAngle = 0;
  prevx = prevy = 512;
  buffer = 50;
  size(400,400);
  // Initialise the ControlIO
  control = ControlIO.getInstance(this);
  // Find a device that matches the configuration file
  gpad = control.getMatchedDevice("PS4");
  if (gpad == null) {
    println("No suitable device configured");
    System.exit(-1); // End the program NOW!
  }
  arduino = new Arduino(this, Arduino.list()[0],57600);
  arduino.pinMode(enl,Arduino.OUTPUT);
  arduino.pinMode(enr,Arduino.OUTPUT);
  arduino.pinMode(l1,Arduino.OUTPUT);
  arduino.pinMode(l2,Arduino.OUTPUT);
  arduino.pinMode(r1,Arduino.OUTPUT);
  arduino.pinMode(r2,Arduino.OUTPUT);
}
int getAngle(int x,int y)
{
  float m1 = (y-512.0)/(x-512.0);
  float m2 = (512.0-512.0)/(1023.0-0.0);  
  int tangle =(int)(atan((m2-m1)/(1.0+m1*m2))*57.3);
  if(x==512)
  {
    if(y>=512) tangle = 270;
    else tangle = 90;
  }
  else if(x < 512) tangle+=180;
  else if(y>512) tangle+=360;
  if(tangle==360) tangle = 0;
  if(x==512 && y==512)
   tangle = 0;
  return tangle;
}
public void draw()
{
  if(mode)
    mode = mode1();
  else
    mode = mode0();
}
public boolean mode0()
{
  int fr,fl,rl,rr,yl,yr;
  fr = rr = fl = rl = 0;
  yl = (int)gpad.getSlider("yLeft").getValue();
  yr = (int)gpad.getSlider("yRight").getValue();
  //Buffering stuff
  if(yl-prevx>buffer)
  {
    yl = prevx+buffer;
  }
  else if(yl-prevx<-buffer)
  {
    yl = prevx-buffer;
  }
  if(yr-prevy>buffer)
  {
    yr = prevy+buffer;
  }
  else if(yr-prevy<-buffer)
  {
    yr = prevy-buffer;
  }
  if(yl>0)
  {
    fl = 1;
    rl = 0;
    powl = (int)map(yl,0,512,0,255);
  }
  else if(yl<0)
  {
    fl = 0;
    rl = 1;
    powl = (int)map(abs(yl),0,512,0,255);
  }
  else if(yl == 0)
  {
    fl = rl = 0;
    powl = 0;
  }
  if(yr>0)
  {
    fr = 0;
    rr = 1;
    powr = (int)map(yr,0,512,0,255);
  }
  else if(yr<0)
  {
    fr = 1;
    rr = 0;
    powr = (int)map(abs(yr),0,512,0,255);
  }
  else if(yr == 0)
  {
    fr = rr = 0;
    powr = 0;
  }
  prevx = yl;
  prevy = yr;
  arduino.analogWrite(enl,powl);
  arduino.analogWrite(enr,powr);
  arduino.digitalWrite(l2,fl);
  arduino.digitalWrite(l1,rl);
  arduino.digitalWrite(r2,fr);
  arduino.digitalWrite(r1,rr);
  if(gpad.getButton("xBut").pressed())
  {
    delay(200);
    return true;
  }
  return false;
}
public boolean mode1()
{
  int fl,rl,fr,rr;
  fl=rl=fr=rr=0;
  background(125);
  textSize(24);
  x = (int)gpad.getSlider("xRight").getValue()+512;
  y = (int)gpad.getSlider("yRight").getValue()+512;
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
  angle = getAngle(x,y);
  int t = (int)sqrt(pow((x-512),2) + pow((y-512),2));
  t = constrain(t,0,512);
  powl = powr = (int)map(t,0,512,0,255);
  rotr = (int)gpad.getSlider("rotateR").getValue();
  rotl = (int)gpad.getSlider("rotateL").getValue();
  if(x==512 && y==512)
  {
    powl = powr = 0; //Power going to 0
    fl = rl = 0; //1st motor rotation stops
    fr = rr = 0; //2nd motor rotation stops
    angle = 0;
  }
  else if(x==512)
  {
    if(y>512)
    {
      powl = powr;
      fl = rr = 0;
      rl = fr = 1;
      currQ = 3;
    }
    else if(y<512)
    {
      powl = powr;
      fl = rr = 1;
      rl = fr = 0;
      currQ = 1;
    }
  }
  else
  {
    if(angle<90)
    {
      currQ = 1;
      fl = rr = 1;
      rl = fr = 0;
      powr = (int)map(angle,0,90,0,255);
    }
    else if(angle<=180 && angle!=90)
    {
      currQ = 2;
      fr = rl = 0;
      rr = fl = 1;
      powl = (int)map(angle,90,180,255,0);
    }
    else if(angle<=270)
    {
      currQ = 3;
      fl = 0; rl = 1;
      fr = 1; rr = 0;
      powl = (int)map(angle,180,270,0,255);
    }
    else if(angle<360)
    {
      currQ = 4;
      fl = 0; rl = 1;
      fr = 1; rr = 0;
      powr = (int)map(angle,270,360,255,0);
    }
  }
  prevx = x;
  prevy = y;
  prevAngle = angle;
  arduino.analogWrite(enl,powl);
  arduino.analogWrite(enr,powr);
  arduino.digitalWrite(l1,fl);
  arduino.digitalWrite(l2,rl);
  arduino.digitalWrite(r1,fr);
  arduino.digitalWrite(r2,rr);
  prevQ = currQ;
  text(Integer.toString(x),20,20);
  text(Integer.toString(y),80,20);
  text(Integer.toString(angle),300,20);
  text(Integer.toString(rotr),20,40);
  text(Integer.toString(rotl),80,40);
  text(Integer.toString(powl),20,60);
  text(Integer.toString(powr),80,60);
  if(gpad.getButton("xBut").pressed())
  {
    delay(200);
    powr = powl = 0;
    fr = fl = rr = rl = 0;
    arduino.analogWrite(enl,powl);
    arduino.analogWrite(enr,powr);
    arduino.digitalWrite(l1,fl);
    arduino.digitalWrite(l2,rl);
    arduino.digitalWrite(r1,fr);
    arduino.digitalWrite(r2,rr);
    return false;
  }
  return true;
}