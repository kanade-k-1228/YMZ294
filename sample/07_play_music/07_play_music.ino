// 曲を選ぶドン！
// #include "makaimura.h"
#include "rockman_dr_wily.h"

#include <PlayMusic.h>
#include <YMZ294.h>

YMZ294 sound(14, 15, 16, 10, 2, 3, 4, 5, 6, 7, 8, 9);

// Data Format
//          15 - 0:Delay 1:Sound
//   IF Delay
//     14 ~  0 - Delay Time [ms]
//   IF Sound
//     14 ~ 13 - Chip Sellect
//     12 ~ 11 - Channel
//     10 ~  4 - Note Number
//      3 ~  0 - Velocity

void play_sound(uint16_t data) {
  if(data & 0b1 << 15) {
    int channel = (data & (0b11 << 11)) >> 11;
    int note_number = (data & (0b1111111 << 4)) >> 4;
    int velocity = data & 0b1111;
    sound.set_freq((Channel)(channel - 1), FREQ_TABLE[note_number]);
    sound.set_volume((Channel)(channel - 1), velocity);
  } else {
    delay(data);
  }
  return;
}

void setup() {
  sound.setup_pin();
  sound.reset_registers();
  delay(1);
  sound.set_mixer(1, 1, 1, 0, 0, 0);
}

void loop() {
  for(int i = 0; i < len; i++) {
    int data = pgm_read_word_near(music + i);
    play_sound(data);
  }
}
