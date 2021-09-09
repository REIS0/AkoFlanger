#include "DistrhoPlugin.hpp"
#include "DistrhoPluginInfo.h"
#include "DistrhoUtils.hpp"
#include "faust/FaustDSP.hpp"
#include <faust/dsp/dsp.h>
#include <faust/gui/MapUI.h>

const auto FREQ = "Frequency";
const auto DEPTH = "Depth";
const auto REGEN = "Regen";
const auto DRY_WET = "Dry/Wet";
const auto LEVEL = "Level";

START_NAMESPACE_DISTRHO

class AkoFlanger : public Plugin {
public:
  AkoFlanger() : Plugin(paramParameterCount, 0, 0) {
    fUI = new MapUI();
    fDSP = new mydsp();
    fDSP->buildUserInterface(fUI);
    fDSP->init(this->getSampleRate());
  }

protected:
  const char *getLabel() const override { return "AkoFlanger"; }
  const char *getDescription() const override {
    return "A simple flanger plugin.";
  }
  const char *getMaker() const override { return "REIS0"; }
  const char *getLicense() const override { return "GNU GPLv3"; }
  uint32_t getVersion() const override { return d_version(0, 1, 0); }
  int64_t getUniqueId() const override { return d_cconst('A', 'k', 'o', 'F'); }

  void initParameter(uint32_t index, Parameter &parameter) override {
    switch (index) {
    case paramFreq:
      parameter.name = FREQ;
      parameter.symbol = "freq";
      parameter.ranges.def = 1.f;
      parameter.ranges.min = 0.1f;
      parameter.ranges.max = 2.f;
      break;
    case paramDepth:
      parameter.name = DEPTH;
      parameter.symbol = "depth";
      parameter.ranges.def = 0.5f;
      parameter.ranges.min = 0.f;
      parameter.ranges.max = 0.9f;
      break;
    case paramRegen:
      parameter.name = REGEN;
      parameter.symbol = "regen";
      parameter.ranges.def = 0.25f;
      parameter.ranges.min = 0.f;
      parameter.ranges.max = 0.5f;
      break;
    case paramDryWet:
      parameter.name = DRY_WET;
      parameter.symbol = "dry_wet";
      parameter.ranges.def = 0.5f;
      parameter.ranges.min = 0.f;
      parameter.ranges.max = 1.f;
      break;
    case paramLevel:
      parameter.name = LEVEL;
      parameter.symbol = "level";
      parameter.ranges.def = 1.f;
      parameter.ranges.min = 0.f;
      parameter.ranges.max = 1.f;
      break;
    default:
      return;
    }
  };

  float getParameterValue(uint32_t index) const override {
    switch (index) {
    case paramFreq:
      return fUI->getParamValue(FREQ);
    case paramDepth:
      return fUI->getParamValue(DEPTH);
    case paramRegen:
      return fUI->getParamValue(REGEN);
    case paramDryWet:
      return fUI->getParamValue(DRY_WET);
    case paramLevel:
      return fUI->getParamValue(LEVEL);
    default:
      return 0.0;
    }
  }

  void setParameterValue(uint32_t index, float value) override {
    switch (index) {
    case paramFreq:
      fUI->setParamValue(FREQ, value);
      break;
    case paramDepth:
      fUI->setParamValue(DEPTH, value);
      break;
    case paramRegen:
      fUI->setParamValue(REGEN, value);
      break;
    case paramDryWet:
      fUI->setParamValue(DRY_WET, value);
      break;
    case paramLevel:
      fUI->setParamValue(LEVEL, value);
      break;
    default:
      break;
    }
  }

  void run(const float **inputs, float **outputs, uint32_t frames) override {
    float *casted_inputs[] = {const_cast<float *>(inputs[0]),
                              const_cast<float *>(inputs[1])};

    fDSP->compute(frames, casted_inputs, outputs);
  }

private:
  MapUI *fUI;
  dsp *fDSP;

  DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AkoFlanger);
};

Plugin *createPlugin() { return new AkoFlanger(); }

END_NAMESPACE_DISTRHO