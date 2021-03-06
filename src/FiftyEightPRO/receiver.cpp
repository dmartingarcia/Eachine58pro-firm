#include <Arduino.h>
#include "led.h"

#define ADDRESS_SYNTH 0x01
#define VIDEO_SWITCH PC15
#define RECEIVER_ID_A 1
#define RECEIVER_ID_B 0
#define RSSI_A PA0
#define RSSI_B PA1
#define RSSI_MIN_VAL 640 
#define RSSI_MAX_VAL 1350
#define MIN_TUNING_DELAY 30
#define SPI_ADDRESS_SYNTH_A 0x01
#define PIN_SPI_SLAVE_SELECT_A  PA4
#define PIN_SPI_SLAVE_SELECT_B  PA3
#define PIN_SPI_CLOCK           PA7
#define PIN_SPI_DATA            PA5

static inline void sendBit(uint8_t value);
static inline void sendBits(uint32_t bits, uint8_t count = 20);
static inline void sendSlaveSelect(uint8_t value);
static inline void sendRegister(uint8_t address, uint32_t data);

namespace Receiver {

  void init(){
    pinMode(VIDEO_SWITCH, OUTPUT);
    pinMode(PIN_SPI_SLAVE_SELECT_A, OUTPUT);
    pinMode(PIN_SPI_SLAVE_SELECT_B, OUTPUT);
    pinMode(PIN_SPI_CLOCK, OUTPUT);
    pinMode(PIN_SPI_DATA, OUTPUT);
  }
  
  void setFreq(uint16_t frec){
    sendRegister(SPI_ADDRESS_SYNTH_A,
                 (((frec - 479) / 2 / 32) << 7) | ((frec - 479) / 2 % 32));
    delay(MIN_TUNING_DELAY);
  }
  
  void setActiveReceiver(int selector){
    if(selector == 0){
      GPIOC->regs->BSRR = 1<<15;
      //digitalWrite(VIDEO_SWITCH, RECEIVER_ID_A);
      Led::on_a();
      Led::off_b();
    }else{
      GPIOC->regs->BRR = 1<<15;
      //digitalWrite(VIDEO_SWITCH, RECEIVER_ID_B);
      Led::on_b();
      Led::off_a();
    }
  }

  uint16_t getRawRssi(uint8_t selector){
    if(selector == RECEIVER_ID_A){
      return analogRead(RSSI_A); 
    }else{
      return analogRead(RSSI_B);
    }
  }
  
  uint8_t getRssi(uint8_t selector){
    return constrain(
                     map(Receiver::getRawRssi(selector),
                         RSSI_MIN_VAL,
                         RSSI_MAX_VAL,
                         0, 
                         100),
                     0,100);
  }
}

// FROM https://github.com/MartinLaza/OpenPRO58
static inline void sendRegister(uint8_t address, uint32_t data) {
  sendSlaveSelect(LOW);
  
  sendBits(address, 4);
  sendBit(HIGH); // Enable write.
  
  sendBits(data, 20);
  
  // Finished clocking data in
  sendSlaveSelect(HIGH);
  GPIOA->regs->BRR = 1<<7;
  GPIOA->regs->BRR = 1<<5;
  //digitalWrite(PIN_SPI_CLOCK, LOW);
  //digitalWrite(PIN_SPI_DATA, LOW);
}

static inline void sendBits(uint32_t bits, uint8_t count) {
  for (uint8_t i = 0; i < count; i++) {
    sendBit(bits & 0x1);
    bits >>= 1;
  }
}

static inline void sendBit(uint8_t value) {
  GPIOA->regs->BRR = 1<<7;
  //digitalWrite(PIN_SPI_CLOCK, LOW);
  delayMicroseconds(1);
  if(value == HIGH){
    GPIOA->regs->BSRR = 1<<5;
  }else{
    GPIOA->regs->BRR = 1<<5;
  }
  //digitalWrite(PIN_SPI_DATA, value);
  delayMicroseconds(1);
  GPIOA->regs->BSRR = 1<<7;
  //digitalWrite(PIN_SPI_CLOCK, HIGH);
  delayMicroseconds(1);
  
  GPIOA->regs->BRR = 1<<7;  
  //digitalWrite(PIN_SPI_CLOCK, LOW);
  delayMicroseconds(1);
}

static inline void sendSlaveSelect(uint8_t value) {
  if(value == HIGH){
    GPIOA->regs->BSRR = 1<<4;
    GPIOA->regs->BSRR = 1<<5;
  }else{
    GPIOA->regs->BRR = 1<<4;
    GPIOA->regs->BRR = 1<<5;
  }
  //digitalWrite(PIN_SPI_SLAVE_SELECT_A, value);
  //digitalWrite(PIN_SPI_SLAVE_SELECT_B, value);
  delayMicroseconds(1);
}
