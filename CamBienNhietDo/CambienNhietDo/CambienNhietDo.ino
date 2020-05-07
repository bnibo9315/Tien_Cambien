#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define DS18B20  A3
OneWire oneWire(DS18B20);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27,20,2); 
int temp ;
#define Motor12V1  6
#define Motor12V2  5

String intro = "MSSV : 1653020083 ";
void setup()
{
  pinMode(Motor12V1, OUTPUT);
  pinMode(Motor12V2, OUTPUT);
  lcd.init();                    
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Lam Van Tien");
  for (int i=0; i<intro.length()-16; i++){
    for (int j=0; j<=16; j++){
      lcd.setCursor(j,1);
      lcd.print(intro[i+j]);
    }
      delay(250);
  }
  sensors.begin();
  delay(1000);
  lcd.clear();
}

void loop()
{
  sensors.requestTemperatures();  
//  MotorfollowTemp();
  Motor6Lv();
  delay(50);
}
void MotorControllerON(int PWM)
{
  digitalWrite(Motor12V1,LOW);
  analogWrite(Motor12V2, PWM); 
  delay(500);
  }void MotorControllerOFF()
{
  digitalWrite(Motor12V1,LOW);
  digitalWrite(Motor12V2, LOW); 
  delay(500);
  }
void displaysreen()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("NhietDo:");
  lcd.setCursor(10,0);
  lcd.print(sensors.getTempCByIndex(0));
  lcd.setCursor(0,1);
  lcd.print("Lv:");
  }
void MotorfollowTemp()
{
   if(sensors.getTempCByIndex(0) < 15)
  {
    MotorControllerOFF();
    displaysreen();
    lcd.setCursor(4,1);
    lcd.print("Off");
    }
  else
  {
    temp = sensors.getTempCByIndex(0) * 3;
    if(temp > 255 )
    {
    MotorControllerON(255);
    displaysreen();
    lcd.setCursor(4,1);
    lcd.print("On Duty:");
    lcd.setCursor(13,1);
    lcd.print("Max");
    }
    else {
    MotorControllerON(temp);
    displaysreen();
    lcd.setCursor(4,1);
    lcd.print("On Duty:");
    lcd.setCursor(13,1);
    lcd.print( sensors.getTempCByIndex(0) * 0.8 );
    lcd.setCursor(15,1);
    lcd.print("%");
      }
  }
  }
void Motor6Lv()
{
   if(sensors.getTempCByIndex(0) < 15)
  {
    MotorControllerOFF();
    displaysreen();
    lcd.setCursor(4,1);
    lcd.print("Off");
    }
  else if(15 <= sensors.getTempCByIndex(0) && sensors.getTempCByIndex(0) < 30)
  {
    MotorControllerON(65);
    displaysreen();
    lcd.setCursor(4,1);
    lcd.print("1");
    lcd.setCursor(6,1);
    lcd.print("Duty: 25%");
  }
  else if (30 <= sensors.getTempCByIndex(0) && sensors.getTempCByIndex(0) < 35)
  {
    MotorControllerON(90);
    displaysreen();
    lcd.setCursor(4,1);
    lcd.print("2");
    lcd.setCursor(6,1);
    lcd.print("Duty: 35%");
    }
  else if (35 <= sensors.getTempCByIndex(0) && sensors.getTempCByIndex(0) < 45)
  {
    MotorControllerON(130);
    displaysreen();
    lcd.setCursor(4,1);
    lcd.print("3");
    lcd.setCursor(6,1);
    lcd.print("Duty: 50%");
    }
  else if (45 <= sensors.getTempCByIndex(0) && sensors.getTempCByIndex(0) < 60)
  {
    MotorControllerON(170);
    displaysreen();
    lcd.setCursor(4,1);
    lcd.print("4");
    lcd.setCursor(6,1);
    lcd.print("Duty: 65%");
    }
    else if (60 <= sensors.getTempCByIndex(0) && sensors.getTempCByIndex(0) < 80)
  {
    MotorControllerON(205);
    displaysreen();
    lcd.setCursor(4,1);
    lcd.print("5");
    lcd.setCursor(6,1);
    lcd.print("Duty: 80%");
    }
    else
  {
    MotorControllerON(255);
    displaysreen();
    lcd.setCursor(4,1);
    lcd.print("6");
    lcd.setCursor(6,1);
    lcd.print("Duty: Max");
    
}
  }
