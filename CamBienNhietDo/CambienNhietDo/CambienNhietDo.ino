////////////////////////////////////////////////////
//  Author : Thanh Quang Long - Founder HNLShop   //
//  Day : 1/6/2020                                //
////////////////////////////////////////////////////
//Notice Bluetooth:
// 1 : ON
// 2 : OFF
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define DS18B20  A3
OneWire oneWire(DS18B20);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27,20,2); 
SoftwareSerial bluetooth(0,1);
float temp ;
char state;
int pwm;

String nhietdo;
#define Motor12V1  6
#define Motor12V2  5

String intro = "MSSV : 1653020083 ";
void setup()
{
  bluetooth.begin(9600); 
  Serial.begin(9600);
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
//  Motor6Lv();
  displaysreen();
  bluetoothDisplay();
  
}

void MotorControllerON(int PWM)
{
  digitalWrite(Motor12V1,LOW);
  analogWrite(Motor12V2, PWM); 
  delay(500);
  }
void MotorControllerOFF()
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
void displaysreenOFF()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("NhietDo:");
  lcd.setCursor(10,0);
  lcd.print(sensors.getTempCByIndex(0));
  lcd.setCursor(0,1);
  lcd.print("Lv: OFF");
      Serial.print(sensors.getTempCByIndex(0));
    Serial.print("                         OFF ");
    Serial.print("\n");
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
    Serial.print(sensors.getTempCByIndex(0));
    Serial.print("                           OFF ");
    Serial.print("\n");
    }
  else if(15 <= sensors.getTempCByIndex(0) && sensors.getTempCByIndex(0) < 30)
  {
    MotorControllerON(75);
    displaysreen();
    lcd.setCursor(4,1);
    lcd.print("1");
    lcd.setCursor(6,1);
    lcd.print("Duty: 25%");
    Serial.print(sensors.getTempCByIndex(0));
    Serial.print(  "                          1 ");
    Serial.print("\n");
  }
  else if (30 <= sensors.getTempCByIndex(0) && sensors.getTempCByIndex(0) < 35)
  {
    MotorControllerON(90);
    displaysreen();
    lcd.setCursor(4,1);
    lcd.print("2");
    lcd.setCursor(6,1);
    lcd.print("Duty: 35%");
    Serial.print(sensors.getTempCByIndex(0));
    Serial.print( "                          2 ");
    Serial.print("\n");
    }
  else if (35 <= sensors.getTempCByIndex(0) && sensors.getTempCByIndex(0) < 45)
  {
    MotorControllerON(130);
    displaysreen();
    lcd.setCursor(4,1);
    lcd.print("3");
    lcd.setCursor(6,1);
    lcd.print("Duty: 50%");
    Serial.print(sensors.getTempCByIndex(0));
    Serial.print( "                         3 ");
    Serial.print("\n");
    }
  else if (45 <= sensors.getTempCByIndex(0) && sensors.getTempCByIndex(0) < 60)
  {
    MotorControllerON(170);
    displaysreen();
    lcd.setCursor(4,1);
    lcd.print("4");
    lcd.setCursor(6,1);
    lcd.print("Duty: 65%");
    Serial.print(sensors.getTempCByIndex(0));
    Serial.print( "                          4 ");
    Serial.print("\n");
    }
    else if (60 <= sensors.getTempCByIndex(0) && sensors.getTempCByIndex(0) < 80)
  {
    MotorControllerON(205);
    displaysreen();
    lcd.setCursor(4,1);
    lcd.print("5");
    lcd.setCursor(6,1);
    lcd.print("Duty: 80%");
    Serial.print(sensors.getTempCByIndex(0));
    Serial.print( "                        5 ");
    Serial.print("\n");
    }
    else
  {
    MotorControllerON(255);
    displaysreen();
    lcd.setCursor(4,1);
    lcd.print("6");
    lcd.setCursor(6,1);
    lcd.print("Duty: Max");
    Serial.print(sensors.getTempCByIndex(0));
    Serial.print("                         6 ");
    Serial.print("\n");
  }
}
void bluetoothDisplay()
{
  if(bluetooth.available() > 0){
    state = bluetooth.read();
    int pwm = bluetooth.read();
 MotorControllerON(pwm);
  } 
  switch (state) {
  case '1':
    displaysreenOFF();
    MotorControllerOFF();
     break;
  case '2':
     displaysreen();
     MotorfollowTemp();
     break;
  case '3':
    displaysreen();
    Motor6Lv();
    break;
// case '4':
//    MotorfollowTemp();
//    break;
    
  default:
   MotorControllerOFF(); 
   break;
}
  }
