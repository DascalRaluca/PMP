#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 
RTC_DS3231 RTC;

int Button1=5; // Button SET pressedCnt
int Button2=6; // Button +
int Button3=7; // Button -

int hourAux;
int minAux;
int yearAux;
int monthAux;
int dayAux;
int pressedCnt =0;

void setup()
{ //setarea initiala a display-ului
  lcd.init();
  lcd.clear();
  lcd.backlight();
  //asignarea pinilor
  pinMode(Button1,INPUT_PULLUP); 
  pinMode(Button2,INPUT_PULLUP);
  pinMode(Button3,INPUT_PULLUP);
  
  Wire.begin();
  RTC.begin();

  int pressedCnt=0;
}
 
void loop()
{ 

  if(digitalRead(Button1)== LOW) 
  {
   pressedCnt=pressedCnt+1;
  }
  // se afiseaza ora si data
  if (pressedCnt==0)
    {
     DisplayDateTime(); 
          }
  // se seteaza ora        
  if (pressedCnt==1)
    {
      SetHour();
    }
   // se seteaza minutul 
  if (pressedCnt==2)
    {
      SetMinute();
    }
  if (pressedCnt==3)
    { 
    pressedCnt=0;
    }

}

void DisplayDateTime ()
{
  // se afiseaza timpul dupa formatul Time: ora:minut
  DateTime now = RTC.now();
  lcd.setCursor(0, 0);
  lcd.print("Time : ");
  lcd.print(now.hour(), DEC);
  hourAux=now.hour();
  lcd.print(":");
  if (now.minute()<=9)
  {
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  minAux=now.minute();

  // se afiseaza data dupa formatul Date: zi.luna.an
  lcd.setCursor(0, 1);
  lcd.print("Date : ");
  
  lcd.print(now.day(), DEC);
  dayAux=now.day();
  lcd.print(".");
  if (now.month()<=9)
  {
    lcd.print("0");
  }
  lcd.print(now.month(), DEC);
  monthAux=now.month();
  lcd.print(".");
  lcd.print(now.year(), DEC);
  yearAux=now.year();
}

// se permite modificarea orei
void SetHour()
{
  lcd.clear();
  if(digitalRead(Button2)==LOW)
  {
    if(hourAux==23)
    {
      hourAux=0;
    }
    else
    {
      hourAux=hourAux+1;
    }
  }
   if(digitalRead(Button3)==LOW)
  {
    if(hourAux==0)
    {
      hourAux=23;
    }
    else
    {
      hourAux=hourAux-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set Hours:");
  lcd.setCursor(0,1);
  lcd.print(hourAux,DEC);
}

//se permite modificare minutului
void  SetMinute()
{
  lcd.clear();
  if(digitalRead(Button2)==LOW)
  {
    if (minAux==59)
    {
      minAux=0;
    }
    else
    {
      minAux=minAux+1;
    }
  }
   if(digitalRead(Button3)==LOW)
  {
    if (minAux==0)
    {
      minAux=59;
    }
    else
    {
      minAux=minAux-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set Minutes:");
  lcd.setCursor(0,1);
  lcd.print(minAux,DEC);

}
  
