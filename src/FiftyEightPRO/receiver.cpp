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
#define TEST_FREC 5771
#define SPI_ADDRESS_SYNTH 0x01
#define PIN_SPI_SLAVE_SELECT_A  PA4
#define PIN_SPI_SLAVE_SELECT_B  PA3
#define PIN_SPI_CLOCK           PA7
#define PIN_SPI_DATA            PA5

static inline void sendBit(uint8_t value);
static inline void sendBits(uint32_t bits, uint8_t count = 20);
static inline void sendSlaveSelect(uint8_t value);
static inline void sendRegister(uint8_t address, uint32_t data);

namespace Receiver {
  
  uint32_t spi_channel_value(int frec){
    int f_lo = ((frec - 479) / 2);
    return ((f_lo / 32) << 7) | (f_lo % 32);
  }
    
  void sendBit(uint8_t value) {
    digitalWrite(PIN_SPI_CLOCK, LOW);
    delayMicroseconds(1);
    
    digitalWrite(PIN_SPI_DATA, value);
    delayMicroseconds(1);
    digitalWrite(PIN_SPI_CLOCK, HIGH);
    delayMicroseconds(1);
    
    digitalWrite(PIN_SPI_CLOCK, LOW);
    delayMicroseconds(1);
  }

  void sendBits(uint32_t bits, uint8_t count) {
    for (uint8_t i = 0; i < count; i++) {
      sendBit(bits & 0x1);
      bits >>= 1;
    }
  }
  
  void setFreq(uint16 frec){
    //SELECT both receivers
    digitalWrite(PIN_SPI_SLAVE_SELECT_A, LOW);
    digitalWrite(PIN_SPI_SLAVE_SELECT_B, LOW);
    delayMicroseconds(1);

    //SELECT register
    Receiver::sendBits(SPI_ADDRESS_SYNTH, 4);

    //ENABLE write
    Receiver::sendBit(HIGH);

    //SEND channel
    
    Receiver::sendBits(Receiver::spi_channel_value(frec), 20);
    
    // DESELECT and disable SPI pins
    digitalWrite(PIN_SPI_SLAVE_SELECT_A, HIGH);
    digitalWrite(PIN_SPI_SLAVE_SELECT_B, HIGH);
    delayMicroseconds(1);
    digitalWrite(PIN_SPI_CLOCK, LOW);
    digitalWrite(PIN_SPI_DATA, LOW);

    //Wait for tuning
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
    uint16_t rssi = 0;
    if(selector == RECEIVER_ID_A){
       rssi = analogRead(RSSI_A);
    }else{
      rssi = analogRead(RSSI_B);
    }

    return constrain(
                     map(rssi,
                         RSSI_MIN_VAL,
                         RSSI_MAX_VAL,
                         0, 
                         100),
                     0,100);
  }
}
 
static inline void sendBits(uint32_t bits, uint8_t count) {
    for (uint8_t i = 0; i < count; i++) {
        sendBit(bits & 0x1);
        bits >>= 1;
    }
}

static inline void sendBit(uint8_t value) {
   digitalWrite(PIN_SPI_CLOCK, LOW);
    delayMicroseconds(1);

    digitalWrite(PIN_SPI_DATA, value);
    delayMicroseconds(1);
    digitalWrite(PIN_SPI_CLOCK, HIGH);
    delayMicroseconds(1);

    digitalWrite(PIN_SPI_CLOCK, LOW);
    delayMicroseconds(1);
}

static inline void sendSlaveSelect(uint8_t value) {
    digitalWrite(PIN_SPI_SLAVE_SELECT_A, value);
    digitalWrite(PIN_SPI_SLAVE_SELECT_B, value);
    delayMicroseconds(1);
}
