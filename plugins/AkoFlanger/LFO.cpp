#include "LFO.hpp"
#include <cmath>
#define TWO_PI 2 * M_PI

LFO::LFO(float freq, int samplerate) {
  this->freq = freq;
  this->t_samples = 1.f / samplerate;
  this->time = 0.f;
  // TODO: add a triangle wave option
  // this->wave_type = 0;
}

float LFO::get_value() {
  // TODO: triangle wave
  // y(t) = A*sin(2pi*f*t + p)
  float y = (std::sin(2.f * TWO_PI * freq * time) * 0.5f) + 0.5f;
  time += t_samples;
  return y;
}

void LFO::set_freq(float freq) { this->freq = freq; }

float LFO::get_freq() const { return freq; }