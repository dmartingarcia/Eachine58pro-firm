#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306_STM32.h>
#include "channel.h"
#include <stdio.h>

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
    display.setTextColor(WHITE);
    display.println(" Fifty");
    display.println(" Eight");
    display.setTextSize(2);
    display.println("    PRO");
    display.display();
    delay(250);
    display.invertDisplay(true);
    delay(250);
    display.invertDisplay(false);
  }

  void diversity_screen(uint8_t rssi_a, uint8_t rssi_b, char selected_channel[2], uint16_t freq, boolean manual){
    display.clearDisplay();
    display.setTextColor(WHITE);

    if(manual){
      display.fillRect(0,0,70,64, WHITE);
      display.setTextColor(BLACK);
    }

    display.setCursor(2, 6);
    display.setTextSize(6);
    display.println(selected_channel);

    display.setCursor(24, 55);
    display.setTextSize(1);
    display.println(freq);

    if(manual){ 
      display.setTextColor(WHITE);
    }
    
    display.drawLine(72, 0, 72, 64, WHITE);
    display.drawLine(72, 32, 128, 32, WHITE);

    display.setCursor(74, 2);
    display.setTextSize(1);
    display.print(rssi_a);
    display.println("%");
    display.fillRect(72, 12, map(rssi_a, 0, 100, 0, 55), 20, WHITE);
    display.setCursor(74, 35);
    display.setTextSize(1);
    display.print(rssi_b);
    display.println("%");
    display.fillRect(72, 45, map(rssi_b, 0, 100, 0, 55), 20, WHITE);
    
    display.display();
  }

  void clear(){
    display.clearDisplay();
  }

  void scan_screen(uint8_t rssi_values[40]){
    display.clearDisplay();
    short max_value = 0;
    short max_index = 0;
    const short offset = 4;
    
    for(int i = 0; i < 40; i++){
      uint8_t normalized_value = map(rssi_values[i],0,100,1,54);
      display.fillRect(offset + i * 3, 64 - normalized_value, 3, 100, WHITE);
      if(normalized_value > max_value){
        max_index = i;
        max_value = normalized_value;
      }
    }

    char channel_name[2];
    sprintf(channel_name, "%c%u", Channel::getBandByIndex(max_index), Channel::getNumByIndex(max_index));

    display.setCursor(offset + max_index * 3 - 4, 64 - max_value - 10);
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.print(channel_name);

    display.display();
  }
}

