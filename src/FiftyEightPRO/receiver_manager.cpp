#include <Arduino.h>
#include "display.h"
#include "receiver.h"
#include "led.h"

namespace ReceiverManager {
  void select(){
    uint8_t rssi_a = Receiver::getRssi(0);
    uint8_t rssi_b = Receiver::getRssi(1);
    uint8_t selected = 0;
    if(rssi_a < rssi_b){
      selected = 1;
      Receiver::setActiveReceiver(1);
    }else{
      selected = 0;
      Receiver::setActiveReceiver(0);
    }
    Display::show_rssi_values(rssi_a, rssi_b, selected);
  }
}
