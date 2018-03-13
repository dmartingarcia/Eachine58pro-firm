#include <SPI.h>
#include <Wire.h>
#include "display.h"
#include "led.h"
#include "receiver.h"
#include "buzzer.h"
#include "channel.h"
#include "button.h";

uint8 state = 1;
boolean longPush = false;
boolean shortPush = false;
long long lastButtonHandling = 0;
volatile boolean upPush = false;
volatile boolean downPush = false;
volatile int okButtonCounter = -1;

void HandleButtonUp(){
  upPush = true;
  Buzzer::beep();
}

void HandleButtonDown(){
  downPush = true;
  Buzzer::beep();
}

void HandleButtonOk(){
  okButtonCounter++;
  Buzzer::beep();
}

void handleButtonTimming(){
  switch(okButtonCounter){
  case(0):
    break;
  case(1):
    shortPush = true;
    longPush = false;
    lastButtonHandling = millis();
    break;
  default:
    shortPush = false;
    longPush = true;
    Buzzer::async_tone(400, 250);
  }
  
  okButtonCounter = 0;
}

void setup() {  
  Display::init();
  Display::show_splashscreen();
  Led::init();
  Led::test();
  Receiver::init();
  Buzzer::init();
  Buzzer::test();
  Receiver::setFreq(5820);
  Button::init();
  
  attachInterrupt(PA8, HandleButtonUp, RISING);
  attachInterrupt(PB12, HandleButtonDown, RISING);
  attachInterrupt(PB14, HandleButtonOk, RISING);
}

void loop(){
  if((lastButtonHandling + 1000) < millis()){   
    handleButtonTimming();
    lastButtonHandling = millis();
  }
  
  switch(state){
  case 1:
    diversity_button_routine();
    diversity_loop();
    break;
  case 2:
    scan_button_routine();
    scan_loop();
    break;
  default:
    state = 1;
  }
}

void scan_button_routine(){
  if(upPush){
    upPush = false;
  }
  if(downPush){
    downPush = false;
  }
  if(shortPush){
    shortPush = false;
  }
  if(longPush){
    longPush = false;
    state = 1;
  }
}

void scan_loop() {
  uint8_t rssi_values[40];

  Display::clear();
  for(int i = 0; i < 40; i++){
    Receiver::setFreq(Channel::getFrequencyByIndex(i));
    char value = max(Receiver::getRssi(0), Receiver::getRssi(1));
    value = max(value, max(Receiver::getRssi(0), Receiver::getRssi(1)));
    //value = max(value, max(Receiver::getRssi(0), Receiver::getRssi(1)));
    //value = max(value, max(Receiver::getRssi(0), Receiver::getRssi(1)));
    //value = max(value, max(Receiver::getRssi(0), Receiver::getRssi(1)));
    
    value = map(value*value,0,10000,0,100);
    
    rssi_values[i] = value;
  }
  
  Display::scan_screen(rssi_values);
  Buzzer::beep();
}

volatile boolean backward_seek = false;
volatile boolean is_tunned = false;
volatile int channel = 0;
volatile boolean manual_seek = false;

void diversity_button_routine(){
  if(upPush){
    is_tunned = false;
    backward_seek = false;
    ++channel;
    upPush = false;
  }
  if(downPush){
    is_tunned = false;
    backward_seek = true;
    --channel;
    downPush = false;
  }
  if(shortPush){
    shortPush = false;
    manual_seek = !manual_seek;
    is_tunned = true;
  }
  if(longPush){
    longPush = false;
    state = 2;
  }
}

void diversity_loop(){
  uint8_t rssi_a, rssi_b;
  char channel_string[2];
  uint16_t frequency; 

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

