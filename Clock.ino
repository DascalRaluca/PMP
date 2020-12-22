#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
RTC_DS3231 RTC;


int button1=6; 
int button2=7;
int button3=8; 
int button4=9;

#define buzzer 10
#define LED 11

int hourAux;
int minAux;
int yearAux;
int monthAux;
int dayAux;
int pressedButton1 =0;

void setup()
{
  //initializare lcd
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  //butoane
  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  pinMode(button3,INPUT_PULLUP);
  pinMode(button4,INPUT_PULLUP);

 //output-uri
  pinMode(LED,OUTPUT);
  pinMode(buzzer, OUTPUT);
   
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  
 if (! RTC.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (RTC.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}
 
void loop()
{
  if(digitalRead(button1)== LOW) 
  {
   pressedButton1=pressedButton1+1;
  }
  if(pressedButton1==0)
  {
    DisplayDateTime();
  }
  if (pressedButton1==1)
    { SetHour();}
  if (pressedButton1==2)
    {SetMinute();}
  if (pressedButton1==3)
    {SetYear();}
  if (pressedButton1==4)
    {SetMonth();}
  if (pressedButton1==5)  
    {SetDay();}
  if (pressedButton1==6)
  {   updateDateTime(); 
      delay(600);
      pressedButton1=0;
  }    
  
  if((digitalRead(button4)== LOW))                                                                                                                                                                     
  {
    SetHourAlarm();
    SeMinutetAlarm();
    lcd.clear();
    lcd.setCursor(6,0);
    lcd.print("Alarm ");
    lcd.setCursor(6,1);
    lcd.print(hour, DEC);
    lcd.print(":");
    if (min<=9)
     {
      lcd.print("0");
      }
    lcd.print(min, DEC);
    delay(1000);
    lcd.clear();
  }
  delay(100);
}

void DisplayDateTime ()
{
  lcd.clear();
  DateTime now = RTC.now();
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  
  lcd.print(now.hour(), DEC);
  hourAux=now.hour();
  lcd.print(":");
  
  if (now.minute()<=9)
  {
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  minAux=now.minute();
  
  lcd.setCursor(0, 1);
  lcd.print("Date: ");
  lcd.print(now.day(), DEC);
  dayAux=now.day();
  
  lcd.print("/");
  if (now.month()<=9)
  {
    lcd.print("0");
  }
  lcd.print(now.month(), DEC);
  monthAux=now.month();
  lcd.print("/");
  lcd.print(now.year(), DEC);
  yearAux=now.year();
}

void SetHour()
{
  lcd.clear();
  DateTime now = RTC.now();
  if(digitalRead(button3)==LOW)
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
   if(digitalRead(button2)==LOW)
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
  lcd.print("Set hour: ");
  lcd.print(hourAux,DEC);
  delay(100);
}

void SetMinute()
{

  lcd.clear();
  if(digitalRead(button3)==LOW)
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
   if(digitalRead(button2)==LOW)
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
  lcd.print("Set minute: ");
  lcd.print(minAux,DEC);
  delay(100);
}

 
void SetYear()
{

  lcd.clear();
  if(digitalRead(button3)==LOW)
  {    
    yearAux=yearAux+1;
  }
   if(digitalRead(button2)==LOW)
  {
    yearAux=yearAux-1;
  }
  lcd.setCursor(0,0);
  lcd.print("Set year: ");
  lcd.print(yearAux,DEC);
  delay(100);
}

void SetMonth()
{
  lcd.clear();
  if(digitalRead(button3)==LOW)
  {
    if (monthAux==12)
    {
      monthAux=1;
    }
    else
    {
      monthAux=monthAux+1;
    }
  }
   if(digitalRead(button2)==LOW)
  {
    if (monthAux==1)
    {
      monthAux=12;
    }
    else
    {
      monthAux=monthAux-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set month: ");
  lcd.print(monthAux,DEC);
  delay(100);
}

void SetDay()
{
  lcd.clear();
  if(digitalRead(button3)==LOW)
  {
    if (dayAux==31)
    {
      dayAux=1;
    }
    else
    {
      dayAux=dayAux+1;
    }
  }
   if(digitalRead(button2)==LOW)
  {
    if (dayAux==1)
    {
      dayAux=31;
    }
    else
    {
      dayAux=dayAux-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set day: ");
  lcd.print(dayAux,DEC);
  delay(100);
}

void updateDateTime()
{
  lcd.clear();
  RTC.adjust(DateTime(yearAux,monthAux,dayAux,hourAux,minAux,0));
  DisplayDateTime();
  delay(100);
} 

void SetHourAlarm()
{
  while(digitalRead(button1)==HIGH){
  lcd.clear();
  if(digitalRead(button3)==LOW)
  {
    if(hour==23)
    {
      hour=0;
    }
    else
    {
      hour=hour+1;
    }
  }
   if(digitalRead(button2)==LOW)
  {
    if(hour==0)
    {
      hour=23;
    }
    else
    {
      hour=hour-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set hour alarm: ");
  lcd.setCursor(7,1);
  lcd.print(hour,DEC);
  delay(100);
 }
 delay(100);
}

void SeMinutetAlarm()
 {
  while(digitalRead(button1)==HIGH){ 

  lcd.clear();
  if(digitalRead(button3)==LOW)
  {
    if (min==59)
    {
      min=0;
    }
    else
    {
      min=min+1;
    }
  }
   if(digitalRead(button2)==LOW)
  {
    if (min==0)
    {
      min=59;
    }
    else
    {
      min=min-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set minute alarm:");
  lcd.setCursor(7,1);
  lcd.print(min,DEC);
  delay(100);
 }
 delay(100);
}
