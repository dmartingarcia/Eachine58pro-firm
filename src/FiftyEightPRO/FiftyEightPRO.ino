#include <SPI.h>
#include <Wire.h>
#include "display.h"
#include "led.h"
#include "receiver.h"
#include "buzzer.h"
#include "channel.h"

uint8 state = 1;

void setup() {
  Display::init();
  Display::show_splashscreen();
  Led::init();
  Led::test();
  Receiver::init();
  Buzzer::init();
  Buzzer::test();
  Receiver::setFreq(5820);
}

void loop(){
  switch(state){
  case 1:
    diversity_loop();
    break;
  case 2:
    scan_loop();
    break;
  }
}

void scan_loop() {
  uint8_t rssi_values[40];
  Display::clear();
  for(int i = 0; i < 40; i++){
    Receiver::setFreq(Channel::getFrequencyByIndex(i));
    char value = max(Receiver::getRssi(0), Receiver::getRssi(1));
    value = max(value, max(Receiver::getRssi(0), Receiver::getRssi(1)));
    value = max(value, max(Receiver::getRssi(0), Receiver::getRssi(1)));
    value = max(value, max(Receiver::getRssi(0), Receiver::getRssi(1)));
    value = max(value, max(Receiver::getRssi(0), Receiver::getRssi(1)));

    value = map(value*value,0,10000,0,100);

    rssi_values[i] = value;
  }
  
  Display::scan_screen(rssi_values);
  Buzzer::beep();
}

volatile boolean backward_seek = false;
volatile boolean is_tunned = false;
volatile int channel;
volatile boolean manual_seek;

void diversity_loop(){
  uint8_t rssi_a, rssi_b;
  char channel_string[2];
  uint16_t frequency; 

  attachInterrupt(PA8, handleButtonUp, RISING);
  attachInterrupt(PB12, handleButtonDown, RISING);
  attachInterrupt(PB14, handleButtonOK, RISING);

  channel = 0;
  manual_seek = false;
  
  while(true){
    if(!is_tunned && !manual_seek){
      if(backward_seek){
        channel--;
      }else{
        channel++;
      }  
    }

    if(channel == 40){
      channel = 0;
    }else if(channel == -1){
      channel = 39;
    }

    frequency = Channel::getFrequencyByIndex(channel);
    Receiver::setFreq(frequency);

    rssi_a = Receiver::getRssi(0);
    rssi_b = Receiver::getRssi(1);
    
    if(rssi_a <= rssi_b){
      Receiver::setActiveReceiver(0);
    }else{
      Receiver::setActiveReceiver(1);
    }
    
    sprintf(channel_string, "%c%u", Channel::getBandByIndex(channel), Channel::getNumByIndex(channel));
    Display::diversity_screen(rssi_a, rssi_b, channel_string, frequency, manual_seek);    
    if(!is_tunned && (rssi_a > 50 || rssi_b > 50)){
      is_tunned = true;
      Buzzer::tone(2000,200);
    }
  }
}

void handleButtonUp(){
  is_tunned = false;
  backward_seek = false;
  ++channel;
}

void handleButtonDown(){
  is_tunned = false;
  backward_seek = true;
  --channel;
}

void handleButtonOK(){
  manual_seek = !manual_seek;
  is_tunned = true;
}
