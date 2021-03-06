#include <Arduino.h>
#define LED_A PB9
#define LED_B PA2

namespace Led{

  void on_a(){
    //digitalWrite(LED_A, LOW);
    GPIOB->regs->BSRR = 1<<9;
  }

  void on_b(){
    //digitalWrite(LED_B, LOW);
    GPIOA->regs->BSRR = 1<<2;
  }

  void off_a(){
    //digitalWrite(LED_A, HIGH);
    GPIOB->regs->BRR = 1<<9;
  }

  void off_b(){
    //digitalWrite(LED_B, HIGH);
    GPIOA->regs->BRR = 1<<2;
  }

  void init(){
    pinMode(LED_A, OUTPUT);
    pinMode(LED_B, OUTPUT);
    Led::off_a();
    Led::off_b();
  }
  
  void test(){
    Led::on_a();
    delay(333);
    Led::off_a();
    delay(333);
    Led::on_b();
    delay(333);
    Led::off_b();
  }
}
