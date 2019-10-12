
#include <Wire.h>
#include<EEPROM.h>
#include <RTClib.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); 
RTC_DS1307 RTC;
int temp,inc,hours1,minut,add=11;
int next=10;    
int INC=9;
int set_mad=8;

#define buzzer 13

int HOUR,MINUT,SECOND;

void setup()
{
 Wire.begin();
 RTC.begin();
 lcd.begin(16,2);
 pinMode(INC, INPUT);
 pinMode(next, INPUT);
 pinMode(set_mad, INPUT);
 pinMode(buzzer, OUTPUT);

   lcd.setCursor(0,0);
   lcd.print("Medicin reminder");
   lcd.setCursor(0,1);
   lcd.print(" Using Arduino  ");
    delay(2000);
    lcd.setCursor(0,0);
   lcd.print("By Saddam khan  ");
   lcd.setCursor(0,1);
   lcd.print("Engineers Garage");
    delay(2000);

 if(!RTC.isrunning())
 {
 RTC.adjust(DateTime(__DATE__,__TIME__));
 }
}

void loop()
{
   int temp=0,val=1,temp4;
   DateTime now = RTC.now();
   if(digitalRead(set_mad) == 0)      //set medicine time
   { 
     lcd.setCursor(0,0);
   lcd.print("  Set Medicine  ");
   lcd.setCursor(0,1);
   lcd.print("  Reminder time ");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter Time 1");
    defualt();
    time(1);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter Time 2");
    defualt();
    delay(1000);
    time(2);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter Time 3");
    defualt();    
time(3);
     lcd.setCursor(0,0);
   lcd.print("Medicin reminder");
   lcd.setCursor(0,1);
   lcd.print("  time has set  ");
    delay(2000);
 }
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Time:");
 lcd.setCursor(6,0);
 lcd.print(HOUR=now.hour(),DEC); 
 lcd.print(":");
 lcd.print(MINUT=now.minute(),DEC);
 lcd.print(":");
 lcd.print(SECOND=now.second(),DEC);
 lcd.setCursor(0,1);
 lcd.print("Date: ");
 lcd.print(now.day(),DEC);
 lcd.print("/");
 lcd.print(now.month(),DEC);
 lcd.print("/");
 lcd.print(now.year(),DEC);
 match();
 delay(200);
}

void defualt()
{
  lcd.setCursor(0,1);
  lcd.print(HOUR);
  lcd.print(":");
  lcd.print(MINUT);
  lcd.print(":");
  lcd.print(SECOND);
}

/*Function to set alarm time and feed time into Internal eeprom*/

void time(int x)  
{
  int temp=1,minuts=0,hours=0,seconds=0;
    while(temp==1)
    {
     if(digitalRead(INC)==0)
     {
      HOUR++;
      if(HOUR==24)
      {
       HOUR=0;
      }
      while(digitalRead(INC)==0);
     }     
lcd.clear();
      lcd.setCursor(0,0);
    lcd.print("Enter Time ");
   lcd.print(x); 
    lcd.setCursor(0,1);
    lcd.print(HOUR);
    lcd.print(":");
    lcd.print(MINUT);
    lcd.print(":");
    lcd.print(SECOND);
    delay(100);
    if(digitalRead(next)==0)
    {
      hours1=HOUR;
      EEPROM.write(add++,hours1);
     temp=2;
     while(digitalRead(next)==0);
    }
    } 
    while(temp==2)
    {     
if(digitalRead(INC)==0)
     {
      MINUT++;
      if(MINUT==60)
      {MINUT=0;}
      while(digitalRead(INC)==0);
     }
      lcd.clear();
      lcd.setCursor(0,0);
    lcd.print("Enter Time ");
   lcd.print(x); 
    lcd.setCursor(0,1);
    lcd.print(HOUR);
    lcd.print(":");
    lcd.print(MINUT);
    lcd.print(":");
    lcd.print(SECOND);
    delay(100);
      if(digitalRead(next)==0)
      {
       minut=MINUT;
       EEPROM.write(add++, minut);
       temp=0;
       while(digitalRead(next)==0);
      }
    }
    delay(1000);
}


/* Function to chack medication time */

void match()
{
  int tem[17];
  for(int i=11;i<17;i++)
  {
    tem[i]=EEPROM.read(i); 
 }
  if(HOUR == tem[11] && MINUT == tem[12]) 
  {
   beep();
   beep();
   beep();
   beep();
   lcd.setCursor(0,0);
   lcd.print("  Take Group One  ");
   lcd.setCursor(0,1);
   lcd.print("     Medicine     ");
   beep();
   beep();
   beep();
   beep();
  }

   if(HOUR == tem[13] && MINUT == tem[14])
   {
      beep();
   beep();
   beep();
   beep();
    lcd.setCursor(0,0);
   lcd.print("  Take Group Two  ");
   lcd.setCursor(0,1);
   lcd.print("     Medicine     ");
    beep();
   beep();
   beep();
   beep();
   }


   if(HOUR == tem[15] && MINUT == tem[16] )
   {  
     beep();
   beep();
   beep();
   beep();
    lcd.setCursor(0,0);
   lcd.print("Take Group Three ");
   lcd.setCursor(0,1);
   lcd.print("     Medicine    ");
   beep();
   beep();
   beep();
   beep();
   }
}

/* function to buzzer indication */

void beep()
{
   digitalWrite(buzzer,HIGH);
   delay(500);
   digitalWrite(buzzer, LOW);
   delay(500);
}
