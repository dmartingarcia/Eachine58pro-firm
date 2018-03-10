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
  ReceiverManager::select();
  delay(200);
}
