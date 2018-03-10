#include <Arduino.h>
#include "led.h"

#define ADDRESS_SYNTH 0x01
#define ADDRESS_POWER 0x0A
#define VIDEO_SWITCH PC15
#define RECEIVER_ID_A 0
#define RECEIVER_ID_B 1
#define RSSI_A PA0
#define RSSI_B PA1
#define RSSI_MIN_VAL 640 
#define RSSI_MAX_VAL 1600
#define MIN_TUNING_DELAY 25


namespace Receiver {
  
  void setFreq(uint16 frec){
    delay(MIN_TUNING_DELAY);
  }
  
  void setActiveReceiver(int selector){
    if(selector==RECEIVER_ID_A){
      digitalWrite(VIDEO_SWITCH, RECEIVER_ID_A);
      Led::on_a();
      Led::off_b();
    }else{
      digitalWrite(VIDEO_SWITCH, RECEIVER_ID_B);
      Led::on_b();
      Led::off_a();
    }
  }
  
  uint8_t getRssi(int selector){
    uint16 rssi = 0;
    if(selector == RECEIVER_ID_A){
       rssi = analogRead(RSSI_A);
    }else{
      rssi = analogRead(RSSI_B);
    }

    rssi = map(rssi,
               RSSI_MIN_VAL,
               RSSI_MAX_VAL,
               0, 
               100);
    return  constrain(rssi,0,100);
  }
}
