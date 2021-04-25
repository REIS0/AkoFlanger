#include "DistrhoPlugin.hpp"
#include "DistrhoPluginInfo.h"
#include "DistrhoUtils.hpp"
#include "Flanger.hpp"
#include "LFO.hpp"
#include <array>
#define MAX_DELAY this->getSampleRate() * 0.05
#define DELAY this->getSampleRate() * 0.02

START_NAMESPACE_DISTRHO

class AkoFlanger : public Plugin {
public:
  AkoFlanger()
      : Plugin(paramParameterCount, 0, 0), flangerL(DELAY, MAX_DELAY),
        flangerR(DELAY, MAX_DELAY), depth(0.5f), regen(0.5f), dry_wet(0.5f),
        lfo(1.f, this->getSampleRate()) {}

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
      parameter.ranges.def = 0.5f;
      parameter.ranges.min = 0.f;
      parameter.ranges.max = 1.f;
      break;
    case paramLFOSpeed:
      parameter.name = "Speed";
      parameter.symbol = "speed";
      parameter.ranges.def = 1.5f;
      parameter.ranges.min = 0.5f;
      parameter.ranges.max = 2.5f;
      break;
    case paramRegenAmount:
      parameter.name = "Regen";
      parameter.symbol = "regen";
      parameter.ranges.def = 0.5f;
      parameter.ranges.min = 0.0f;
      parameter.ranges.max = 1.f;
      break;
    case paramDryWet:
      parameter.name = "Dry/Wet";
      parameter.symbol = "dry_wet";
      parameter.ranges.def = 0.5f;
      parameter.ranges.min = 0.1f;
      parameter.ranges.max = 1.f;
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
    case paramDryWet:
      return dry_wet;
    default:
      return 0.0f;
    }
  }

  void setParameterValue(uint32_t index, float value) override {
    switch (index) {
    case paramDepth:
      depth = value;
      break;
    case paramLFOSpeed:
      lfo.set_freq(value); // needs smoothing
      break;
    case paramRegenAmount:
      regen = value;
      break;
    case paramDryWet:
      dry_wet = value;
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
      outL[i] =
          (1 - dry_wet) * inL[i] + dry_wet * flangerL.process(n, depth, inL[i]);
      outR[i] =
          (1 - dry_wet) * inR[i] + dry_wet * flangerR.process(n, depth, inR[i]);
      // TODO: feedback modulation
    }
  }

private:
  // TODO: stack flangers
  // TODO: test cubic interpolation

  Flanger flangerL;
  Flanger flangerR;

  // std::array<Flanger, 3> flangersL;
  // std::array<Flanger, 3> flangersR;

  // PARAMS

  float depth;
  float regen;

  float dry_wet;

  LFO lfo;

  // TODO: invert depth operation
  // bool invert;

  DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AkoFlanger);
};

Plugin *createPlugin() { return new AkoFlanger(); }

END_NAMESPACE_DISTRHO