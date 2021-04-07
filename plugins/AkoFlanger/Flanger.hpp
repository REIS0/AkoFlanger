#include "RingBuffer.hpp"
// TODO

class Flanger {
public:
  Flanger(int buffer_size);
  float process(float n, float x);

private:
  float cubic_interpolation(float finpos, float xm1, float x0, float x1,
                            float x2);

  RingBuffer buffer; // feedforward buffer

  int p = 0;
  int buffer_size;
};