#include "YMZ294.h"

YMZ294::YMZ294(byte YMZ294_CS, byte YMZ294_WR, byte YMZ294_A0, byte YMZ294_IC,
               byte YMZ294_D0, byte YMZ294_D1, byte YMZ294_D2, byte YMZ294_D3,
               byte YMZ294_D4, byte YMZ294_D5, byte YMZ294_D6, byte YMZ294_D7)
    : YMZ294_CS(YMZ294_CS), YMZ294_WR(YMZ294_WR), YMZ294_A0(YMZ294_A0), YMZ294_IC(YMZ294_IC),
      YMZ294_D0(YMZ294_D0), YMZ294_D1(YMZ294_D1), YMZ294_D2(YMZ294_D2), YMZ294_D3(YMZ294_D3),
      YMZ294_D4(YMZ294_D4), YMZ294_D5(YMZ294_D5), YMZ294_D6(YMZ294_D6), YMZ294_D7(YMZ294_D7) {}

void YMZ294::setup_pin() {
  pinMode(YMZ294_CS, OUTPUT);
  pinMode(YMZ294_WR, OUTPUT);
  pinMode(YMZ294_A0, OUTPUT);
  pinMode(YMZ294_IC, OUTPUT);
  pinMode(YMZ294_D0, OUTPUT);
  pinMode(YMZ294_D1, OUTPUT);
  pinMode(YMZ294_D2, OUTPUT);
  pinMode(YMZ294_D3, OUTPUT);
  pinMode(YMZ294_D4, OUTPUT);
  pinMode(YMZ294_D5, OUTPUT);
  pinMode(YMZ294_D6, OUTPUT);
  pinMode(YMZ294_D7, OUTPUT);
}

void YMZ294::set_register(Register addr, byte value) {
  digitalWrite(YMZ294_CS, 0);
  // Set Address
  digitalWrite(YMZ294_WR, 0);
  digitalWrite(YMZ294_A0, 0);
  digitalWrite(YMZ294_D0, (byte)addr & 0b00000001);
  digitalWrite(YMZ294_D1, (byte)addr & 0b00000010);
  digitalWrite(YMZ294_D2, (byte)addr & 0b00000100);
  digitalWrite(YMZ294_D3, (byte)addr & 0b00001000);
  digitalWrite(YMZ294_D4, (byte)addr & 0b00010000);
  digitalWrite(YMZ294_D5, (byte)addr & 0b00100000);
  digitalWrite(YMZ294_D6, (byte)addr & 0b01000000);
  digitalWrite(YMZ294_D7, (byte)addr & 0b10000000);
  // Latch
  digitalWrite(YMZ294_WR, 1);
  // Set Value
  digitalWrite(YMZ294_WR, 0);
  digitalWrite(YMZ294_A0, 1);
  digitalWrite(YMZ294_D0, value & 0b00000001);
  digitalWrite(YMZ294_D1, value & 0b00000010);
  digitalWrite(YMZ294_D2, value & 0b00000100);
  digitalWrite(YMZ294_D3, value & 0b00001000);
  digitalWrite(YMZ294_D4, value & 0b00010000);
  digitalWrite(YMZ294_D5, value & 0b00100000);
  digitalWrite(YMZ294_D6, value & 0b01000000);
  digitalWrite(YMZ294_D7, value & 0b10000000);
  // Latch
  digitalWrite(YMZ294_WR, 1);
  // End
  digitalWrite(YMZ294_WR, 0);
  digitalWrite(YMZ294_CS, 1);
}

void YMZ294::reset_registers(void) {
  digitalWrite(YMZ294_CS, 0);
  digitalWrite(YMZ294_IC, 1);
  delay(1);
  digitalWrite(YMZ294_IC, 0);
  delay(1);
  digitalWrite(YMZ294_IC, 1);
  digitalWrite(YMZ294_CS, 0);
}

void YMZ294::set_freq(Channel channel, int freq) {
  word freqbit = (BASE_FREQ / freq) & 0b0000111111111111;  // 12bit
  set_register((Register)((byte)Register::A_L + ((byte)channel * 2)), freqbit & 0xff);
  set_register((Register)((byte)Register::A_U + ((byte)channel * 2)), (freqbit >> 8) & 0xff);
}

void YMZ294::set_noise_freq(int freq) {
  byte freqbit = (BASE_FREQ / freq) & 0b00011111;  // 5bit
  set_register(Register::NOISE, freqbit);
}

void YMZ294::set_mixer(bool A_sound, bool B_sound, bool C_sound, bool A_noise, bool B_noise, bool C_noise) {
  word mixer = (!A_sound << 0) | (!B_sound << 1) | (!C_sound << 2)
               | (!A_noise << 3) | (!B_noise << 4) | (!C_noise << 5);
  set_register(Register::MIXER, mixer);
}

void YMZ294::set_envelope(int freq, word shape) {
  word freqbit = (BASE_FREQ / freq);  // 16bit
  set_register(Register::ENV_L, freqbit & 0xff);
  set_register(Register::ENV_U, (freqbit >> 8) & 0xff);
  set_register(Register::ENV_SHAPE, shape);
}

void YMZ294::set_volume(Channel channel, byte volume_dB, bool use_envelope) {
  set_register((Register)((byte)Register::VOL_A + (byte)channel),
               (((use_envelope << 4) & 0x10) | (volume_dB & 0x1f)));
}
