#include "DistrhoPlugin.hpp"
#include "DistrhoPluginInfo.h"
#include "DistrhoUtils.hpp"
#include "LFO.hpp"
#include "RingBuffer.hpp"
#define BUFFER_SIZE 2048
// ? set samplerate from the host ?
#define SAMPLERATE 48000

START_NAMESPACE_DISTRHO

class AkoFlanger : public Plugin {
public:
  AkoFlanger()
      : Plugin(paramParameterCount, 0, 0), delay((int) SAMPLERATE * 0.025),
        ff_bufferR(delay), ff_bufferL(delay), fd_bufferR(delay),
        fd_bufferL(delay), p1(delay * 0.6 - delay), p2(delay * 0.8 - delay),
        p3(0), depth(0.5), regen(0.5), out_gain(0.8), lfo(5.0, SAMPLERATE) {}

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
      break;
    case paramOutGain:
      parameter.name = "Output Gain";
      parameter.symbol = "out_gain";
      parameter.ranges.def = 0.8;
      parameter.ranges.min = 0.1;
      parameter.ranges.max = 1.0;
      parameter.hints = kParameterIsOutput;
      break;
    default:
      return;
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
    case paramOutGain:
      return out_gain;
    default:
      return 0.0;
    }
  }

  void setParameterValue(uint32_t index, float value) override {
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
    case paramOutGain:
      out_gain = value;
      break;
    default:
      break;
    }
  }

  void run(const float **inputs, float **outputs, uint32_t frames) override {
    const float *const inL = inputs[0];
    const float *const inR = inputs[1];
    float *const outL = outputs[0];
    float *const outR = outputs[1];
    for (uint32_t i = 0; i < frames; ++i) {
      float n = lfo.get_value();
      vL = n * (ff_bufferL.get_value(p3) - vL) + ff_bufferL.get_value(p3 - 1);
      vR = n * (ff_bufferR.get_value(p3) - vR) + ff_bufferR.get_value(p3 - 1);
      outL[i] = inL[i] + depth * vL - regen * fd_bufferL.get_value(p3);
      outR[i] = inR[i] + depth * vR - regen * fd_bufferL.get_value(p3);
      ff_bufferL.set_value(p3, inL[i]);
      ff_bufferR.set_value(p3, inR[i]);
      fd_bufferL.set_value(p3, outL[i]);
      fd_bufferR.set_value(p3, outR[i]);
      p3++;
      if (p3 >= delay3) {
        p3 = 0;
      }
    }
  }

private:
  int delay; // max delay

  RingBuffer ff_bufferR; // feedforward buffer
  RingBuffer ff_bufferL;
  RingBuffer fd_bufferR; // feedback buffer
  RingBuffer fd_bufferL;

  // the pivots for each delay line
  int p1;
  int p2;
  int p3;

  // y(n - 1) from allpass interpolation
  float vL = 0;
  float vR = 0;

  // PARAMS

  float depth;
  float regen;

  float out_gain;

  LFO lfo;

  // TODO: invert depth operation
  // bool invert;

  DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AkoFlanger);
};

Plugin *createPlugin() { return new AkoFlanger(); }

END_NAMESPACE_DISTRHO