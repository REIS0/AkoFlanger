#include "DistrhoPlugin.hpp"
#include "DistrhoPluginInfo.h"
#include "DistrhoUtils.hpp"
#include "LFO.hpp"
#include "RingBuffer.hpp"
#define BUFFER_SIZE 2048
// ? set samplerate from the host ?
#define SAMPLERATE 48000

class AkoFlanger : public Plugin {
public:
  AkoFlanger()
      : Plugin(paramParameterCount, 0, 0), ff_buffer(BUFFER_SIZE),
        fd_buffer(BUFFER_SIZE), delay1(BUFFER_SIZE * 0.6),
        delay2(BUFFER_SIZE * 0.8), delay3(BUFFER_SIZE),
        p1(delay1 - BUFFER_SIZE), p2(delay2 - BUFFER_SIZE), p3(delay3),
        lfo(5.0, SAMPLERATE) {}

protected:
  const char *getLabel() const override { return "AkoFlanger"; }
  const char *getDescription() const override {
    return "A simple experimental flanger plugin.";
  }
  const char *getMaker() const override { return "REIS0"; }
  const char *getLicense() const override { return "GPL-3.0"; }
  uint32_t getVersion() const override { return d_version(0, 0, 0); }
  int64_t getUniqueId() const override { return d_cconst('A', 'k', 'o', 'F'); }

  void initParameter(uint32_t index, Parameter &parameter) override {
    if (index >= paramParameterCount) {
      return;
    }

    switch (index) {
    case paramDepth:
      parameter.name = "Depth";
      parameter.symbol = "depth";
      parameter.ranges.def = 0.5;
      parameter.ranges.min = 0.0;
      parameter.ranges.max = 1.0;
      break;
    case paramLFOSpeed:
      parameter.name = "Speed";
      parameter.symbol = "speed";
      parameter.ranges.def = 5.0;
      parameter.ranges.min = 1.0;
      parameter.ranges.max = 10.0;
      break;
    case paramRegenAmount:
      parameter.name = "Regen";
      parameter.symbol = "regen";
      parameter.ranges.def = 0.5;
      parameter.ranges.min = 0.0;
      parameter.ranges.max = 1.0;
    }
  };

  float getParameterValue(uint32_t index) const override {
    switch (index) {
    case paramDepth:
      return depth;
    case paramLFOSpeed:
      return lfo.get_freq();
    case paramRegenAmount:
      return regen;
    default:
      return 0.0;
    }
  }

  void setParameterValue(uint32_t index, float value) override {
    if (index >= paramParameterCount) {
      return;
    }

    switch (index) {
    case paramDepth:
      depth = value;
      break;
    case paramLFOSpeed:
      lfo.set_freq(value);
      break;
    case paramRegenAmount:
      regen = value;
      break;
    }
  }

  void run(const float **, float **outputs, uint32_t frames) override;

private:
  RingBuffer ff_buffer; // feedforward buffer
  RingBuffer fd_buffer; // feedback buffer

  int delay1;
  int delay2;
  int delay3; // the max delay value

  // the pivots for each delay line
  int p1;
  int p2;
  int p3;

  // PARAMS

  float depth;
  float regen;

  LFO lfo;

  // TODO: invert depth operation
  // bool invert;
};