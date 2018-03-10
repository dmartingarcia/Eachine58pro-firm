namespace Receiver {
  void setFreq(uint16 frec);
  void setActiveReceiver(int selector);
  uint8_t getRssi(int selector);
  uint32_t spi_channel_value(int frec);
  void sendBits(uint32_t bits, uint8_t count);
  void sendBit(uint8_t value);
}
