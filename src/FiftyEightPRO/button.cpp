#include <Arduino.h>
#define BUTTON_UP           PA8
#define BUTTON_MODE         PB14
#define BUTTON_DOWN         PB12

boolean pushed = false;
short button_pushed = 0;


namespace Button {
  void init(){
    pinMode(BUTTON_UP, INPUT);
    pinMode(BUTTON_MODE, INPUT);
    pinMode(BUTTON_DOWN, INPUT);
  }
}
