//Tells if roommate in room
#include <LiquidCrystal.h>
#include <Key.h>
#include <Keypad.h>

int trigPin1 = 0;
int echoPin1 = 1;
int trigPin2 = 2;
int echoPin2 = 3;
int ledPin = 13;
const byte rows = 4;
const byte cols = 4;

char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'5','6','7','C'},
  {'*','0','#','D'}
};

byte rowPins[rows] = {11,10,9,8};
byte colPins[cols] = {7,6,5,4};

Keypad keypad = Keypad(makeKeymap(keys),rowPins,colPins,rows,cols);
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(trigPin1,INPUT);
  pinMode(echoPin1,INPUT);
  pinMode(trigPin2,INPUT);
  pinMode(echoPin2,INPUT);
  pinMode(ledPin,OUTPUT);
}

boolean isCorrect(char c)
{//1 character is being passed from the loop
    int i=0;String t=""; 
    t = t+c;
    for(i=0;i<3;)
    {
      char key = keypad.getKey();
      if(int(key)!=0)
      {
        //Serial.println(key);
        t=t+key;
        i++;
      }
    }//2 passwords are 1612 and 2358
    if(t.equals("1612")) return true;
    else if(t.equals("2358")) return true; 
    else return false;
}

void loop() {
  // put your main code here, to run repeatedly:
    lcd.clear();
    lcd.noDisplay();//turns off display
    char pass;//stores one no. of the code
    boolean ayush = false,akash = false;//counters
    long duration1,distance1,duration2,distance2;//counts the duration and time for ultrasonic sensors
    digitalWrite(trigPin1,HIGH);
    delay(0.05);
    digitalWrite(trigPin1,LOW);
    duration1 = pulseIn(echoPin1,HIGH);
    distance1 = (duration1/2)/29.1;//convert time to cm
    digitalWrite(trigPin2,HIGH);
    delay(0.05);
    digitalWrite(trigPin2,LOW);
    duration2 = pulseIn(echoPin2,HIGH);
    distance2 = (duration2/2)/29.1;
    if(distance1<30)
    {
       ayush = !ayush;
       digitalWrite(ledPin,HIGH);
       delay(5000);
       digitalWrite(ledPin,LOW);
    }
    if(distance2<30)
    {
      akash = !akash;
      digitalWrite(ledPin,HIGH);
      delay(5000);
      digitalWrite(ledPin,LOW);
    }
    pass = keypad.getKey();
    if(int(pass)!=0)
    {
      boolean flag = isCorrect(pass);
      if(flag)
      {
        if(ayush)
        {
          lcd.setCursor(0,0);
          lcd.print("Ayush is in his");
          lcd.setCursor(0,1);
          lcd.print("room - A");
        }
        else if(akash)
        {
          lcd.setCursor(0,0);
          lcd.print("Akash is in his");
          lcd.setCursor(0,1);
          lcd.print("room - B");
        }
        else if(akash && ayush)
        {
          lcd.setCursor(0,0);
          lcd.print("They both are");
          lcd.setCursor(0,1);
          lcd.print("in their room");
        }
        else 
        {
          lcd.setCursor(0,0);
          lcd.print("No one is");
          lcd.setCursor(0,1);
          lcd.print("in the room");
        }
      }
    }
    delay(500);
}
