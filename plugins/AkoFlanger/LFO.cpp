#include "LFO.hpp"
#include <cmath>
#define TWO_PI 2 * M_PI

LFO::LFO(float freq, int samplerate) {
  this->freq = freq;
  this->t_samples = 1 / samplerate;
  this->time = 0;
  // TODO: add a triangle wave option
  this->wave_type = 0;
}

float LFO::get_value() {
  float y;
  // TODO: triangle wave
  // y(t) = A*sin(2pi*f*t + p)
  y = (std::sin(2 * TWO_PI * freq * time) * 0.5) + 0.5;
  time += t_samples;
  return y;
}

void LFO::set_freq(int freq) { this->freq = freq; }

float LFO::get_freq() const { return freq; }