#include "YMZ294.h"

YMZ294::YMZ294(byte PIN_CS, byte PIN_WR, byte PIN_A0, byte PIN_IC,
               byte PIN_D0, byte PIN_D1, byte PIN_D2, byte PIN_D3,
               byte PIN_D4, byte PIN_D5, byte PIN_D6, byte PIN_D7)
    : PIN_CS(PIN_CS), PIN_WR(PIN_WR), PIN_A0(PIN_A0), PIN_IC(PIN_IC),
      PIN_D0(PIN_D0), PIN_D1(PIN_D1), PIN_D2(PIN_D2), PIN_D3(PIN_D3),
      PIN_D4(PIN_D4), PIN_D5(PIN_D5), PIN_D6(PIN_D6), PIN_D7(PIN_D7) {}

void YMZ294::setup_pin() {
  pinMode(PIN_CS, OUTPUT);
  pinMode(PIN_WR, OUTPUT);
  pinMode(PIN_A0, OUTPUT);
  pinMode(PIN_IC, OUTPUT);
  pinMode(PIN_D0, OUTPUT);
  pinMode(PIN_D1, OUTPUT);
  pinMode(PIN_D2, OUTPUT);
  pinMode(PIN_D3, OUTPUT);
  pinMode(PIN_D4, OUTPUT);
  pinMode(PIN_D5, OUTPUT);
  pinMode(PIN_D6, OUTPUT);
  pinMode(PIN_D7, OUTPUT);
}

void YMZ294::set_register(Register addr, byte value) {
  digitalWrite(PIN_CS, 0);
  // Set Address
  digitalWrite(PIN_WR, 0);
  digitalWrite(PIN_A0, 0);
  digitalWrite(PIN_D0, (byte)addr & 0b00000001);
  digitalWrite(PIN_D1, (byte)addr & 0b00000010);
  digitalWrite(PIN_D2, (byte)addr & 0b00000100);
  digitalWrite(PIN_D3, (byte)addr & 0b00001000);
  digitalWrite(PIN_D4, (byte)addr & 0b00010000);
  digitalWrite(PIN_D5, (byte)addr & 0b00100000);
  digitalWrite(PIN_D6, (byte)addr & 0b01000000);
  digitalWrite(PIN_D7, (byte)addr & 0b10000000);
  // Latch
  digitalWrite(PIN_WR, 1);
  // Set Value
  digitalWrite(PIN_WR, 0);
  digitalWrite(PIN_A0, 1);
  digitalWrite(PIN_D0, value & 0b00000001);
  digitalWrite(PIN_D1, value & 0b00000010);
  digitalWrite(PIN_D2, value & 0b00000100);
  digitalWrite(PIN_D3, value & 0b00001000);
  digitalWrite(PIN_D4, value & 0b00010000);
  digitalWrite(PIN_D5, value & 0b00100000);
  digitalWrite(PIN_D6, value & 0b01000000);
  digitalWrite(PIN_D7, value & 0b10000000);
  // Latch
  digitalWrite(PIN_WR, 1);
  // End
  digitalWrite(PIN_WR, 0);
  digitalWrite(PIN_CS, 1);
}

void YMZ294::reset_registers(void) {
  digitalWrite(PIN_CS, 0);
  digitalWrite(PIN_IC, 1);
  delay(1);
  digitalWrite(PIN_IC, 0);
  delay(1);
  digitalWrite(PIN_IC, 1);
  digitalWrite(PIN_CS, 0);
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
