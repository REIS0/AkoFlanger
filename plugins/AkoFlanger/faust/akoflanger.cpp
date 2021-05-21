/* ------------------------------------------------------------
name: "akoflanger"
Code generated with Faust 2.30.7 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

class mydspSIG0 {
	
  private:
	
	int iRec1[2];
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
	}
	int getNumOutputsmydspSIG0() {
		return 1;
	}
	int getInputRatemydspSIG0(int channel) {
		int rate;
		switch ((channel)) {
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	int getOutputRatemydspSIG0(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 0;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	void instanceInitmydspSIG0(int sample_rate) {
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iRec1[l1] = 0;
		}
	}
	
	void fillmydspSIG0(int count, float* table) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec1[0] = (iRec1[1] + 1);
			table[i] = std::sin((9.58738019e-05f * float((iRec1[0] + -1))));
			iRec1[1] = iRec1[0];
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float ftbl0mydspSIG0[65536];

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	int IOTA;
	float fVec0[1024];
	FAUSTFLOAT fHslider1;
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider2;
	float fRec3[2];
	float fRec2[2];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider3;
	float fRec0[1024];
	float fVec1[1024];
	float fRec4[1024];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("compile_options", "-lang cpp -es 1 -scal -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.1");
		m->declare("filename", "akoflanger.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "akoflanger");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.1");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.1");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 2;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	static void classInit(int sample_rate) {
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(65536, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = ((0.00499999989f * fConst0) + 1.0f);
		fConst2 = (1.0f / fConst0);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(0.5f);
		fHslider2 = FAUSTFLOAT(1.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(0.5f);
	}
	
	virtual void instanceClear() {
		IOTA = 0;
		for (int l0 = 0; (l0 < 1024); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec3[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec2[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 1024); l4 = (l4 + 1)) {
			fRec0[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 1024); l5 = (l5 + 1)) {
			fVec1[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 1024); l6 = (l6 + 1)) {
			fRec4[l6] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("akoflanger");
		ui_interface->addHorizontalSlider("Depth", &fHslider3, 0.5f, 0.100000001f, 0.899999976f, 0.00999999978f);
		ui_interface->addHorizontalSlider("Dry/Wet", &fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("Frequency", &fHslider2, 1.0f, 0.100000001f, 2.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("Regen", &fHslider1, 0.5f, 0.100000001f, 0.899999976f, 0.00999999978f);
		ui_interface->addCheckButton("invert depth", &fCheckbox0);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = float(fHslider1);
		float fSlow2 = (0.00100000005f * float(fHslider2));
		float fSlow3 = float(fHslider3);
		float fSlow4 = (int(float(fCheckbox0)) ? (1.0f - fSlow3) : fSlow3);
		float fSlow5 = (1.0f - fSlow0);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[(IOTA & 1023)] = fTemp0;
			fRec3[0] = (fSlow2 + (0.999000013f * fRec3[1]));
			float fTemp1 = (fRec2[1] + (fConst2 * fRec3[0]));
			fRec2[0] = (fTemp1 - std::floor(fTemp1));
			float fTemp2 = (fConst0 * ((0.00300000003f * ftbl0mydspSIG0[int((65536.0f * fRec2[0]))]) + 0.00200000009f));
			int iTemp3 = int(fTemp2);
			int iTemp4 = int(std::min<float>(fConst1, float(std::max<int>(0, iTemp3))));
			int iTemp5 = (iTemp4 + 1);
			float fTemp6 = std::floor(fTemp2);
			float fTemp7 = (fTemp6 + (1.0f - fTemp2));
			float fTemp8 = (fTemp2 - fTemp6);
			int iTemp9 = int(std::min<float>(fConst1, float(std::max<int>(0, (iTemp3 + 1)))));
			int iTemp10 = (iTemp9 + 1);
			fRec0[(IOTA & 1023)] = (fTemp0 + ((fSlow1 * ((fRec0[((IOTA - iTemp5) & 1023)] * fTemp7) + (fTemp8 * fRec0[((IOTA - iTemp10) & 1023)]))) + (fSlow4 * ((fTemp7 * fVec0[((IOTA - iTemp4) & 1023)]) + (fTemp8 * fVec0[((IOTA - iTemp9) & 1023)])))));
			output0[i] = FAUSTFLOAT(((fSlow0 * fRec0[((IOTA - 0) & 1023)]) + (fSlow5 * fTemp0)));
			float fTemp11 = float(input1[i]);
			fVec1[(IOTA & 1023)] = fTemp11;
			fRec4[(IOTA & 1023)] = (fTemp11 + ((fSlow1 * ((fTemp7 * fRec4[((IOTA - iTemp5) & 1023)]) + (fTemp8 * fRec4[((IOTA - iTemp10) & 1023)]))) + (fSlow4 * ((fTemp7 * fVec1[((IOTA - iTemp4) & 1023)]) + (fTemp8 * fVec1[((IOTA - iTemp9) & 1023)])))));
			output1[i] = FAUSTFLOAT(((fSlow0 * fRec4[((IOTA - 0) & 1023)]) + (fSlow5 * fTemp11)));
			IOTA = (IOTA + 1);
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
		}
	}

};

#endif
