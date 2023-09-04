#include <YMZ294.h>

YMZ294 sound(14, 15, 16, 10, 2, 3, 4, 5, 6, 7, 8, 9);

void setup() {
  sound.setup_pin();
  sound.reset_registers();
  delay(1);
  sound.set_freq(Channel::A, 442);
  sound.set_mixer(1, 0, 0, 1, 0, 0);
  sound.set_volume(Channel::A, 15);
}

void loop() {
  for (int i = 0; i < 10000; i++)
    sound.set_noise_freq(i);
}
