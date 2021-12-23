/* ------------------------------------------------------------
author: "REIS0"
license: "GNU GPLv3"
name: "AkoFlanger"
version: "0.1"
Code generated with Faust 2.30.5 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/
 
#include <math.h>
#include <algorithm>

#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"

using std::max;
using std::min;

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/


/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <math.h>

class mydspSIG0 {
	
  private:
	
	int iRec2[2];
	
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
			iRec2[l1] = 0;
		}
	}
	
	void fillmydspSIG0(int count, float* table) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec2[0] = (iRec2[1] + 1);
			table[i] = std::sin((9.58738019e-05f * float((iRec2[0] + -1))));
			iRec2[1] = iRec2[0];
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
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	int IOTA;
	float fVec0[1024];
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	FAUSTFLOAT fHslider4;
	float fRec4[2];
	float fRec3[2];
	float fRec0[2];
	float fVec1[1024];
	float fRec5[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "REIS0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("compile_options", "-lang cpp -es 1 -scal -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.1");
		m->declare("filename", "akoflanger.dsp");
		m->declare("license", "GNU GPLv3");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "AkoFlanger");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.1");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.1");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "0.1");
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
		fConst1 = (0.00499999989f * fConst0);
		fConst2 = (fConst1 + 1.0f);
		fConst3 = (1.0f / fConst0);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1.0f);
		fHslider1 = FAUSTFLOAT(0.5f);
		fHslider2 = FAUSTFLOAT(0.5f);
		fHslider3 = FAUSTFLOAT(0.25f);
		fHslider4 = FAUSTFLOAT(1.0f);
	}
	
	virtual void instanceClear() {
		IOTA = 0;
		for (int l0 = 0; (l0 < 1024); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec4[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec3[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec0[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 1024); l5 = (l5 + 1)) {
			fVec1[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec5[l6] = 0.0f;
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
		ui_interface->openVerticalBox("AkoFlanger");
		ui_interface->declare(&fHslider4, "0", "");
		ui_interface->addHorizontalSlider("Frequency", &fHslider4, 1.0f, 0.100000001f, 2.0f, 0.00999999978f);
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->addHorizontalSlider("Depth", &fHslider2, 0.5f, 0.100000001f, 0.899999976f, 0.00999999978f);
		ui_interface->declare(&fHslider3, "2", "");
		ui_interface->addHorizontalSlider("Regen", &fHslider3, 0.25f, 0.0f, 0.5f, 0.00999999978f);
		ui_interface->declare(&fHslider1, "3", "");
		ui_interface->addHorizontalSlider("Dry/Wet", &fHslider1, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider0, "4", "");
		ui_interface->addHorizontalSlider("Level", &fHslider0, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = float(fHslider1);
		float fSlow2 = (0.600000024f * fSlow1);
		float fSlow3 = float(fHslider2);
		float fSlow4 = float(fHslider3);
		float fSlow5 = (0.00100000005f * float(fHslider4));
		float fSlow6 = (1.0f - fSlow1);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			float fTemp1 = (fTemp0 + (fSlow4 * fRec0[1]));
			fVec0[(IOTA & 1023)] = fTemp1;
			fRec4[0] = (fSlow5 + (0.999000013f * fRec4[1]));
			float fTemp2 = (fRec3[1] + (fConst3 * fRec4[0]));
			fRec3[0] = (fTemp2 - std::floor(fTemp2));
			float fTemp3 = (fConst1 * ((0.5f * ftbl0mydspSIG0[int((65536.0f * fRec3[0]))]) + 0.479999989f));
			int iTemp4 = int(fTemp3);
			int iTemp5 = int(std::min<float>(fConst2, float(std::max<int>(0, iTemp4))));
			float fTemp6 = std::floor(fTemp3);
			float fTemp7 = (fTemp6 + (1.0f - fTemp3));
			float fTemp8 = (fTemp3 - fTemp6);
			int iTemp9 = int(std::min<float>(fConst2, float(std::max<int>(0, (iTemp4 + 1)))));
			fRec0[0] = (fSlow3 * ((fVec0[((IOTA - iTemp5) & 1023)] * fTemp7) + (fTemp8 * fVec0[((IOTA - iTemp9) & 1023)])));
			float fRec1 = fTemp1;
			output0[i] = FAUSTFLOAT((fSlow0 * ((fSlow2 * (fRec0[0] + fRec1)) + (fSlow6 * fTemp0))));
			float fTemp10 = float(input1[i]);
			float fTemp11 = (fTemp10 + (fSlow4 * fRec5[1]));
			fVec1[(IOTA & 1023)] = fTemp11;
			fRec5[0] = (fSlow3 * ((fTemp7 * fVec1[((IOTA - iTemp5) & 1023)]) + (fTemp8 * fVec1[((IOTA - iTemp9) & 1023)])));
			float fRec6 = fTemp11;
			output1[i] = FAUSTFLOAT((fSlow0 * ((fSlow2 * (fRec5[0] + fRec6)) + (fSlow6 * fTemp10))));
			IOTA = (IOTA + 1);
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec0[1] = fRec0[0];
			fRec5[1] = fRec5[0];
		}
	}

};

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

// Factory API
dsp* createmydsp() { return new mydsp(); }

/********************END ARCHITECTURE SECTION (part 2/2)****************/

#endif
