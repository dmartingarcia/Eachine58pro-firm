#include <Arduino.h>

namespace Led{

  void on_a(){
    digitalWrite(PA2, LOW);
  }

  void on_b(){
    digitalWrite(PB9, LOW);
  }

  void off_a(){
    digitalWrite(PA2, HIGH);
  }

  void off_b(){
    digitalWrite(PB9, HIGH);
  }

  void init(){
    pinMode(PA2, OUTPUT);
    pinMode(PB9, OUTPUT);
    Led::off_a();
    Led::off_b();
  }
  
  void test(){
    Led::on_a();
    delay(1000);
    Led::off_a();
    delay(1000);
    Led::on_b();
    delay(1000);
    Led::off_b();
    delay(1000);
  }
}
