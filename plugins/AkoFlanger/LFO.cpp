#include "LFO.hpp"
#include <cmath>
#define TWO_PI 2 * M_PI

LFO::LFO(int freq, int samplerate) {
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
  y = (std::sin(2 * TWO_PI * this->freq * this->time) * 0.5) + 0.5;
  this->time += this->t_samples;
  return y;
}