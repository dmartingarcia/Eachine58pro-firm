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
    display.setCursor(0, 1);
    display.setTextSize(3);
    display.setTextColor(BLACK, WHITE); // 'inverted' text
    display.println("EACHINE 58PRO ");
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.println(" basestylo");
    display.display();
    delay(2000);
    display.invertDisplay(true);
    delay(500);
    display.invertDisplay(false);
    delay(200);
    display.invertDisplay(true);
    delay(200);
    display.invertDisplay(false);
    delay(100);
    display.invertDisplay(true);
    delay(100);
    display.invertDisplay(false);
  }
}

