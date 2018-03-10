namespace Receiver {
  void setFreq(uint16_t frec);
  void setActiveReceiver(int selector);
  uint8_t getRssi(uint8_t selector);
  uint32_t spi_channel_value(int frec);
  void sendBits(uint32_t bits, uint8_t count);
  void sendBit(uint8_t value);
}
