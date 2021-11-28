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
}

void loop() {
  sound.set_envelope(10, 0b0000);
  delay(5000);
  sound.set_envelope(10, 0b0100);
  delay(5000);
  sound.set_envelope(10, 0b1000);
  delay(5000);
  sound.set_envelope(10, 0b1001);
  delay(5000);
  sound.set_envelope(10, 0b1010);
  delay(5000);
  sound.set_envelope(10, 0b1011);
  delay(5000);
  sound.set_envelope(10, 0b1100);
  delay(5000);
  sound.set_envelope(10, 0b1101);
  delay(5000);
  sound.set_envelope(10, 0b1110);
  delay(5000);
  sound.set_envelope(10, 0b1111);
  delay(5000);
}
