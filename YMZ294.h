#ifndef YMZ294_H
#define YMZ294_H

#include "Arduino.h"

const unsigned int FREQ_TABLE[] = {
    0, 9, 9, 10, 10, 11, 12, 12, 13, 14, 15, 15,
    16, 17, 18, 19, 21, 22, 23, 25, 26, 28, 29, 31,
    33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62,
    65, 69, 73, 78, 82, 87, 93, 98, 104, 110, 117, 124,
    131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247,
    262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,
    523, 554, 587, 622, 659, 699, 740, 784, 831, 880, 932, 988,
    1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,
    2093, 2218, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951,
    4186, 4435, 4699, 4978, 5274, 5587, 5920, 6272, 6645, 7040, 7459, 7902,
    8372, 8870, 9397, 9956, 10548, 11175, 11840, 12544};

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
  const byte YMZ294_CS;  // Chip Select
  const byte YMZ294_WR;  // Write Enable
  const byte YMZ294_A0;  // Address / Data Select
  const byte YMZ294_IC;  // Reset
  const byte YMZ294_D0, YMZ294_D1, YMZ294_D2, YMZ294_D3, YMZ294_D4, YMZ294_D5, YMZ294_D6, YMZ294_D7;
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
