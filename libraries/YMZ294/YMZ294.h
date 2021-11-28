#ifndef YMZ294_H
#define YMZ294_H

#include "Arduino.h"

enum class Register : byte {
  A_L = 0x00,       // A Frequency Lower Bit
  A_U = 0x01,       // A Frequency Upper Bit
  B_L = 0x02,       // B Frequency Upper Bit
  B_U = 0x03,       // B Frequency Lower Bit
  C_L = 0x04,       // C Frequency Lower Bit
  C_U = 0x05,       // C Frequency Upper Bit
  NOISE = 0x06,     // Noise Frequency
  MIXER = 0x07,     // Mixer
  VOL_A = 0x08,     // A Volume
  VOL_B = 0x09,     // B Volume
  VOL_C = 0x0A,     // C Volume
  ENV_L = 0x0B,     // Envelope Frequency Lower Bit
  ENV_U = 0x0C,     // Envelope Frequency Upper Bit
  ENV_SHAPE = 0x0D  // Envelope Shape
};

enum class Channel : byte {
  A = 0x00,
  B = 0x01,
  C = 0x02,
};

class YMZ294 {
private:
  // Arduino Pins
  const byte PIN_CS;  // Chip Select
  const byte PIN_WR;  // Write Enable
  const byte PIN_A0;  // Address / Data Select
  const byte PIN_IC;  // Reset
  const byte PIN_D0, PIN_D1, PIN_D2, PIN_D3, PIN_D4, PIN_D5, PIN_D6, PIN_D7;
  const long int BASE_FREQ = 125000;
  const int CH_COUNT = 3;

public:
  YMZ294(byte CS, byte WR, byte A0, byte IC,
         byte D0, byte D1, byte D2, byte D3,
         byte D4, byte D5, byte D6, byte D7);
  void setup_pin();                              // Set Pin Mode
  void set_register(Register addr, byte value);  // Set Register
  void set_register(byte addr, byte value);      // Set Register
  void reset_registers(void);                    // Hardware reset
  void set_freq(Channel channel, int freq);
  void set_noise_freq(int freq);
  void set_mixer(bool A_sound, bool B_sound, bool C_sound, bool A_noise, bool B_noise, bool C_noise);
  void set_envelope(int freq, word shape);
  void set_volume(Channel channel, byte volume_dB, bool use_envelope = false);  // 0~15
};

#endif
