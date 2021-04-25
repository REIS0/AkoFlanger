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
  // ? vectors sem precisar de uma classe separada ?
  RingBuffer buffer; // feedforward buffer

  // std::vector<float> vecbuffer;

  int p = 0;
};