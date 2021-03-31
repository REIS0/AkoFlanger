#include <vector>

class RingBuffer {
public:
  RingBuffer(int buffer_size);
  float get_value(int index);
  void set_value(int index, float value);

private:
  int buffer_size;
  std::vector<float> buffer;
  int rotate_index(int index);
};