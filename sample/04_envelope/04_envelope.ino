#include <YMZ294.h>

YMZ294 sound(14, 15, 16, 10, 2, 3, 4, 5, 6, 7, 8, 9);

void setup() {
  sound.setup_pin();
  sound.reset_registers();
  delay(1);
  sound.set_freq(Channel::A, 442);
  sound.set_freq(Channel::B, 589);
  sound.set_freq(Channel::C, 663);
  sound.set_mixer(1, 1, 1, 0, 0, 0);
  sound.set_volume(Channel::A, 15, true);
  sound.set_volume(Channel::B, 15, true);
  sound.set_volume(Channel::C, 15, true);
  sound.set_envelope(10, 0b1110);
}

void loop() {}
