#include <IRremote.h>
//#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

// функции даты и времени с использованием часов реального времени DS1307, подключенные по I2C. В скетче используется библиотека Wire lib

#include <Wire.h>
#include<LiquidCrystal.h>
#include "RTClib.h"
#include "IRremote.h"
IRrecv irrecv(10); 
decode_results results;
RTC_DS1307 RTC;
LiquidCrystal lcd(7,6,5,4,3,2);

int Relay=8;

void setup () {
  pinMode(Relay , OUTPUT); 
irrecv.enableIRIn(); // запускаем прием
Serial.begin(9600); // выставляем скорость COM порта
  
  lcd.begin(16, 2);                  // Задаем размерность экрана
//lcd.begin(57600);
Wire.begin();
RTC.begin();
if ( !RTC.isrunning()) {
 lcd.setCursor(0, 0);  
lcd.print("RTC is not run!");
         //1234567890123456
// строка ниже используется для настройки даты и времени часов
}
RTC.adjust(DateTime(__DATE__, __TIME__));
//else
lcd.clear();  

}
void loop () {




// рассчитываем дату: 7 дней и 30 секунд

//DateTime future (now.unixtime() + 7 * 86400L + 30);
 DateTime now = RTC.now();
 //lcd.setCursor(0, 0);
// lcd.clear();  
 lcd.setCursor(3,0);
lcd.print(now.year(), DEC);
lcd.print('/');
lcd.print(now.month(), DEC);
lcd.print('/');
lcd.print(now.day(), DEC);
lcd.setCursor(4, 1);
if(now.hour()<10)
lcd.print("0");
lcd.print(now.hour(), DEC);
lcd.print(':');
if(now.minute()<10)
lcd.print("0");
lcd.print(now.minute(), DEC);
lcd.print(':');
if(now.second()<10)
lcd.print("0");
lcd.print(now.second(), DEC);
delay(10);
//if((now.hour() >= 0) && (now.minute() >=32))
//digitalWrite(Relay, HIGH);
//if ((now.hour() >= 0) && (now.minute() >=35))
//digitalWrite(Relay, LOW);
if((now.hour() >= 0) && (now.minute() >=49) && (now.hour() <= 0) && (now.minute() <=52))
digitalWrite(Relay, HIGH);
else 
digitalWrite(Relay, LOW);

//ir+remoutcontroler
 if ( irrecv.decode( &results )) { // если данные пришли
    Serial.println( results.value, HEX ); // печатаем данные
    irrecv.resume(); // принимаем следующую команду
  }

}


