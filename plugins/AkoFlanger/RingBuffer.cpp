#include "RingBuffer.hpp"

/* ----- PUBLIC ----- */

RingBuffer::RingBuffer(int buffer_size) {
  this->buffer_size = buffer_size;
  this->buffer.assign(buffer_size, 0.0);
}

float RingBuffer::get_value(int index) {
  return buffer.at(rotate_index(index));
}

void RingBuffer::set_value(int index, float value) {
  buffer[rotate_index(index)] = value;
}

/* ----- PRIVATE ----- */

int RingBuffer::rotate_index(int index) {
  if (index >= buffer_size)
    return index - buffer_size;
  else if (index < 0)
    return buffer_size + index;
  else
    return index;
}