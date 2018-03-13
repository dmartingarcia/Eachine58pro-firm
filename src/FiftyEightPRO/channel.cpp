#include <avr/pgmspace.h>

static const uint16_t channelFreqTable[] PROGMEM = {
  5865, 5845, 5825, 5805, 5785, 5765, 5745, 5725, // A
  5733, 5752, 5771, 5790, 5809, 5828, 5847, 5866, // B
  5705, 5685, 5665, 5645, 5885, 5905, 5925, 5945, // E
  5740, 5760, 5780, 5800, 5820, 5840, 5860, 5880, // F
  5658, 5695, 5732, 5769, 5806, 5843, 5880, 5917  // R
};

static const uint16_t channelSortFreqIndex[] PROGMEM = {
  31, 28, 24, 20, 17, 13, 10,  6, // A
   8, 11, 15, 18, 22, 25, 29, 32, // B
   5,  3,  2,  0, 35, 36, 38, 39, // E
   9, 12, 16, 19, 23, 26, 30, 34, // F
   1,  4,  7, 14, 21, 27, 33, 37  // R
};

static const uint16_t channelSortTable[] PROGMEM = {
  5645, 5658, 5665, 5685, 5695, 5705, 5725, 5732, // 0-7
  5733, 5740, 5745, 5752, 5760, 5765, 5769, 5771, // 8-15
  5780, 5785, 5790, 5800, 5805, 5806, 5809, 5820, // 16-23
  5825, 5828, 5840, 5843, 5845, 5847, 5860, 5865, // 24-31
  5866, 5880, 5880, 5885, 5905, 5917, 5925, 5945  // 32-39
};

namespace Channel {
  uint16_t getFrequencyByIndex(uint8_t index) {
    return pgm_read_word_near(channelSortTable + index);
  }

  char getBandByIndex(uint8_t index){
    char bands[] = "ABEFR";
    
    return bands[pgm_read_word_near(channelSortFreqIndex + index)/8];
  }

  uint8_t getNumByIndex(uint8_t index){
    return (pgm_read_word_near(channelSortFreqIndex + index)%8)+1;
  }
}
