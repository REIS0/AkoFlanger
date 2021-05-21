#include "Flanger.hpp"

/* ----- PUBLIC ----- */

Flanger::Flanger(int delay, int max_delay)
    : delay(delay), max_delay(max_delay), diff(max_delay - delay),
      buffer(max_delay) {}

// use external LFO
float Flanger::process(float n, float depth, float x) {
  // float y = x + depth * cubic_interpolation(n, buffer.get_value(p),
  //                                           buffer.get_value(p + diff *
  //                                           0.33), buffer.get_value(p + diff
  //                                           * 0.66), buffer.get_value(p +
  //                                           diff));
  float vnm = buffer.get_value(p + diff);
  float v = buffer.get_value(p) - n * vnm;
  float y = x + depth * (n * v + vnm);
  buffer.set_value(p, v);
  // ? maybe useless ?
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