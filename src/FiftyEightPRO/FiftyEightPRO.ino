#include <SPI.h>
#include <Wire.h>
#include "display.h"
#include "led.h"
#include "receiver.h"
#include "receiver_manager.h"
#include "buzzer.h"

void setup() {
  Display::init();
  Display::show_splashscreen();
  Led::init();
  Led::test();
  Buzzer::init();
  Buzzer::beep();
  Receiver::setFreq(5820);
}

void loop() {
  ReceiverManager::select();
}
