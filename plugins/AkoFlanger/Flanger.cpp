#include "Flanger.hpp"

/* ----- PUBLIC ----- */

Flanger::Flanger(int delay, int max_delay)
    : delay(delay), max_delay(max_delay), diff(max_delay - delay), buffer(max_delay) {
  // vecbuffer.assign(max_delay, 0.0f);
}

// use external LFO
float Flanger::process(float n, float depth, float x) {
  float y = x + depth * cubic_interpolation(n, buffer.get_value(p),
                                            buffer.get_value(p + diff *
                                            0.33), buffer.get_value(p + diff
                                            * 0.66), buffer.get_value(p +
                                            diff));
  buffer.set_value(p, x);
  // float y = x + depth * cubic_interpolation(
  //                           n, vecbuffer.front(), vecbuffer.at(diff * 0.33),
  //                           vecbuffer.at(diff * 0.66), vecbuffer.at(diff));
  // vecbuffer.erase(vecbuffer.begin());
  // vecbuffer.push_back(x);
  p++;
  if (p >= max_delay) {
    p = 0;
  }
  return y;
}

/* ----- PRIVATE ----- */

// SOURCE:
// https://www.musicdsp.org/en/latest/Other/49-cubic-interpollation.html
float Flanger::cubic_interpolation(float finpos, float xm1, float x0, float x1,
                                   float x2) {
  float a = (3.f * (x0 - x1) - xm1 - x2) * 0.5f;
  float b = 2.f * x1 + xm1 - (5.f * x0 + x2) * 0.5f;
  float c = (x1 - xm1) * 0.5f;
  return (((a * finpos) + b) * finpos + c) * finpos + x0;
}