#include "RingBuffer.hpp"
#include <vector>

class Flanger {
public:
  Flanger(int delay, int max_delay);
  float process(float n, float depth, float x);

private:
  float cubic_interpolation(float finpos, float xm1, float x0, float x1,
                            float x2);

  int delay;
  int max_delay;
  int diff;
  RingBuffer buffer; // feedforward buffer

  int p = 0;
};