namespace Display {
  void init();
  void show_splashscreen();
  void diversity_screen(uint8_t rssi_a, uint8_t rssi_b, char selected_channel[2], uint16_t freq, boolean manual);
  void scan_screen(uint8_t rssi_values[40]);
  void clear();
}
