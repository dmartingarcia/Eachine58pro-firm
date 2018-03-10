#include <SPI.h>
#include <Wire.h>
#include "display.h"
#include "led.h"
#include "receiver.h"
#include "receiver_manager.h"

void setup() {
  Display::init();
  Display::show_splashscreen();
  Led::init();
  Led::test();
}

void loop() {
  Receiver::setFreq(5771);
  ReceiverManager::select(5771);
  delay(2000);
}
