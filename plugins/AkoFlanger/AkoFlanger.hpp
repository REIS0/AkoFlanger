#include "DistrhoPlugin.hpp"
#include "DistrhoPluginInfo.h"
#include "DistrhoUtils.hpp"
#include "LFO.hpp"
#include "RingBuffer.hpp"

class AkoFlanger : public Plugin {
public:
  AkoFlanger();

protected:
  const char *getLabel() const override { return "AkoFlanger"; }
  const char *getDescription() const override {
    return "A simple experimental flanger plugin.";
  }
  const char *getMaker() const override { return "REIS0"; }
  const char *getLicense() const override { return "GPL-3.0"; }
  uint32_t getVersion() const override { return d_version(0, 0, 0); }
  int64_t getUniqueId() const override { return d_cconst('A', 'k', 'o', 'F'); }

  void initParameter(uint32_t index, Parameter &parameter) override;
  float getParameterValue(uint32_t index) const override;
  void setParameterValue(uint32_t index, float value) override;

  void run(const float **, float **outputs, uint32_t frames) override;

private:
  RingBuffer ff_buffer; // feedforward buffer
  RingBuffer fd_buffer; // feedback buffer

  int delay1;
  int delay2;
  int delay3; // the max delay value

  LFO lfo;

  // TODO: invert depth operation
  // bool invert;
};