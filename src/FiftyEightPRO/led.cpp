#include <Arduino.h>
#define LED_A PB9
#define LED_B PA2

namespace Led{

  void on_a(){
    digitalWrite(LED_A, LOW);
  }

  void on_b(){
    digitalWrite(LED_B, LOW);
  }

  void off_a(){
    digitalWrite(LED_A, HIGH);
  }

  void off_b(){
    digitalWrite(LED_B, HIGH);
  }

  void init(){
    pinMode(LED_A, OUTPUT);
    pinMode(LED_B, OUTPUT);
    Led::off_a();
    Led::off_b();
  }
  
  void test(){
    Led::on_a();
    delay(500);
    Led::off_a();
    delay(500);
    Led::on_b();
    delay(500);
    Led::off_b();
    delay(500);
  }
}
