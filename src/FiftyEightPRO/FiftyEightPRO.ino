#include <SPI.h>
#include <Wire.h>
#include "display.h"
#include "led.h"
#include "receiver.h"

void setup() {
  Display::init();
  Display::show_splashscreen();
  Led::init();
  Led::test();
}

void loop() {
  uint8_t rssi_a = Receiver::getRssi(0);
  uint8_t rssi_b = Receiver::getRssi(1);
  Display::show_rssi_values(rssi_a, rssi_b);
  delay(200);
}
