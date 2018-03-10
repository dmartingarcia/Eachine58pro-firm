#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306_STM32.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

namespace Display {
  
  void init() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
  }
 
  void show_splashscreen() {
    display.clearDisplay();
    display.setCursor(0, 1);
    display.setTextSize(3);
    display.setTextColor(BLACK, WHITE); // 'inverted' text
    display.println("EACHINE 58PRO ");
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.println(" basestylo");
    display.display();
    delay(500);
    display.invertDisplay(true);
    delay(200);
    display.invertDisplay(false);
    delay(100);
    display.invertDisplay(true);
    delay(100);
    display.invertDisplay(false);
    delay(50);
    display.invertDisplay(true);
    delay(50);
    display.invertDisplay(false);
  }

  void show_rssi_values(uint8_t rssi_a, uint8_t rssi_b, uint8_t selected, uint16_t frec_set){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("RSSI_A:");
    display.println(rssi_a);    
    display.print("RSSI_B:");
    display.println(rssi_b);
    display.print("SELECTED:");
    display.println(selected);
    display.print("Frec:");
    display.println(frec_set);    
    display.display();
  }
}

