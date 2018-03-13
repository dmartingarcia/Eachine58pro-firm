#include <Arduino.h>
#define PIN_BUZZER PB8

namespace Buzzer {
  void init(){
    pinMode(PIN_BUZZER, OUTPUT);
  }
  
  void beep(){
    tone(PIN_BUZZER, 800, 30);
  }

  void async_tone(int frec, int millis){ 
    tone(PIN_BUZZER, frec, millis);
  }

  void tone(int frec, int millis){ 
    tone(PIN_BUZZER, frec, millis);
    delay(millis);
  }

  void test(){
    Buzzer::tone(349*3, 150);
    Buzzer::tone(349*3, 150);
    Buzzer::tone(440*3, 200);
    Buzzer::tone(523*3, 250);
    Buzzer::tone(440*3, 200);
    Buzzer::tone(523*3, 350);
  }
}
