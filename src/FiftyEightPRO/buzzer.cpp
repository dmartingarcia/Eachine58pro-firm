#include <Arduino.h>
#define PIN_BUZZER PB8

namespace Buzzer {
  void init(){
    pinMode(PIN_BUZZER, OUTPUT);
  }
  
  void beep(){
    tone(PIN_BUZZER, 2000, 100);
  }
}
