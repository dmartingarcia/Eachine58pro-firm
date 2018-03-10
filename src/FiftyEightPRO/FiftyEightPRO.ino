#include <SPI.h>
#include <Wire.h>
#include "display.h"
#include "led.h"

void setup() {
  Display::init();
  Led::init();
  Led::test();
  Display::show_splashscreen();
}

void loop() {
  Led::test();
}
