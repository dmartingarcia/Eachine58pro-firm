namespace Receiver {
  void init();
  void setFreq(uint16_t frec);
  void setActiveReceiver(int selector);
  uint8_t getRssi(uint8_t selector);
  uint16_t getRawRssi(uint8_t selector);
}
