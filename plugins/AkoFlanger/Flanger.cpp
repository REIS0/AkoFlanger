#include "Flanger.hpp"

/* ----- PUBLIC ----- */

Flanger::Flanger(int buffer_size)
    : buffer(buffer_size), buffer_size(buffer_size) {}

// use external LFO
// ? external depth ? 
float Flanger::process(float n, float x) {
  float y =
      x + cubic_interpolation(n, buffer.get_value(p - 1), buffer.get_value(p),
                              buffer.get_value(p + 1), buffer.get_value(p + 2));
  buffer.set_value(p, x);
  p++;
  if (p >= buffer_size) {
    p = 0;
  }
  return y;
}

/* ----- PRIVATE ----- */

// SOURCE:
// https://www.musicdsp.org/en/latest/Other/49-cubic-interpollation.html
float Flanger::cubic_interpolation(float finpos, float xm1, float x0, float x1,
                                   float x2) {
  float a = (3 * (x0 - x1) - xm1 - x2) * 0.5;
  float b = 2 * x1 + xm1 - (5 * x0 + x2) * 0.5;
  float c = (x1 - xm1) * 0.5;
  float y = (((a * finpos) + b) * finpos + c) * finpos + x0;
  return y;
}