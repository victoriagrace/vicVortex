//----------------------------------------------------------
//
// Code generated with Faust 0.9.92 (http://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#ifndef FAUSTPOWER
#define FAUSTPOWER
#include <cmath>
template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x)            { return 1; }
template <> 	 inline int faustpower<1>(int x)            { return x; }
template <> 	 inline int faustpower<2>(int x)            { return x*x; }
template <int N> inline float faustpower(float x)            { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline float faustpower<0>(float x)          { return 1; }
template <> 	 inline float faustpower<1>(float x)          { return x; }
template <> 	 inline float faustpower<2>(float x)          { return x*x; }
#endif
// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Simple Faust architecture file to easily integrate a Faust DSP module
// in a JUCE project

// needed by any Faust arch file
/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

 ************************************************************************
 ************************************************************************/
 
#ifndef __misc__
#define __misc__

#include <algorithm>
#include <map>
#include <string.h>
#include <stdlib.h>

/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

 ************************************************************************
 ************************************************************************/
 
#ifndef __meta__
#define __meta__

struct Meta
{
    virtual void declare(const char* key, const char* value) = 0;
    virtual ~Meta() {};
};

#endif

using std::max;
using std::min;

struct XXXX_Meta : std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

struct MY_Meta : Meta, std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

inline int lsr(int x, int n)	{ return int(((unsigned int)x) >> n); }

inline int int2pow2(int x)		{ int r = 0; while ((1<<r) < x) r++; return r; }

inline long lopt(char* argv[], const char* name, long def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
	return def;
}

inline bool isopt(char* argv[], const char* name)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
	return false;
}

inline const char* lopts(char* argv[], const char* name, const char* def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
	return def;
}

#endif


// allows to control a Faust DSP module in a simple manner by using parameter's path
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <vector>
#include <map>
#include <string>

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
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
 
#ifndef FAUST_UI_H
#define FAUST_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust User Interface
 * This abstract class contains only the method that the faust compiler can
 * generate to describe a DSP interface.
 ******************************************************************************/

class UI
{

    public:

        UI() {}

        virtual ~UI() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
};

//----------------------------------------------------------------
//  Generic decorator
//----------------------------------------------------------------

class DecoratorUI : public UI
{
    protected:
    
        UI* fUI;

    public:
    
        DecoratorUI(UI* ui = 0):fUI(ui)
        {}

        virtual ~DecoratorUI() { delete fUI; }

        // -- widget's layouts
        virtual void openTabBox(const char* label)          { fUI->openTabBox(label); }
        virtual void openHorizontalBox(const char* label)   { fUI->openHorizontalBox(label); }
        virtual void openVerticalBox(const char* label)     { fUI->openVerticalBox(label); }
        virtual void closeBox()                             { fUI->closeBox(); }

        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)         { fUI->addButton(label, zone); }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)    { fUI->addCheckButton(label, zone); }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
            { fUI->addVerticalSlider(label, zone, init, min, max, step); }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 	
            { fUI->addHorizontalSlider(label, zone, init, min, max, step); }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 			
            { fUI->addNumEntry(label, zone, init, min, max, step); }

        // -- passive widgets	
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
            { fUI->addHorizontalBargraph(label, zone, min, max); }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
            { fUI->addVerticalBargraph(label, zone, min, max); }

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) { fUI->declare(zone, key, val); }

};

#endif
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            replace(res.begin(), res.end(), ' ', '_');
            return res;
        }
    
};

#endif  // FAUST_PATHBUILDER_H

/*******************************************************************************
 * MapUI : Faust User Interface
 * This class creates a map of complete hierarchical path and zones for each UI items.
 ******************************************************************************/

class MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Complete path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
    public:
        
        MapUI() {};
        virtual ~MapUI() {};
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openHorizontalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openVerticalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void closeBox()
        {
            fControlsLevel.pop_back();
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // set/get
        void setParamValue(const std::string& path, float value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            }
        }
        
        float getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                return 0.;
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getMap() { return fPathZoneMap; }
        
        int getParamsCount() { return fPathZoneMap.size(); }
        
        std::string getParamAdress(int index) 
        { 
            std::map<std::string, FAUSTFLOAT*>::iterator it = fPathZoneMap.begin();
            while (index-- > 0 && it++ != fPathZoneMap.end()) {}
            return (*it).first;
        }
};

#endif // FAUST_MAPUI_H

// needed by any Faust arch file
/************************************************************************
    IMPORTANT NOTE : this file contains two clearly delimited sections :
    the ARCHITECTURE section (in two parts) and the USER section. Each section
    is governed by its own copyright and license. Please check individually
    each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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
 
/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/

#ifndef __dsp__
#define __dsp__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class UI;
struct Meta;

/**
* Signal processor definition.
*/

class dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the UI* parameter with instance specific calls
         * to 'addBtton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the UI* user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Returns the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /** Global init, calls the following methods :
         * - static class 'classInit' : static table initialisation
         * - 'instanceInit' : constants and instance table initialisation
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void init(int samplingRate) = 0;
    
        /** Init instance state
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void instanceInit(int samplingRate) = 0;
    
        /** Init instance constant state
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void instanceConstants(int samplingRate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (delay lines...) */
        virtual void instanceClear() = 0;
    
        /**  
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value metadata).
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with sucessive in/out audio buffers.
         *
         * @param count - the nomber of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation : alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the nomber of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         *
         */
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = 0):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int samplingRate) { fDSP->init(samplingRate); }
        virtual void instanceInit(int samplingRate) { fDSP->instanceInit(samplingRate); }
        virtual void instanceConstants(int samplingRate) { fDSP->instanceConstants(samplingRate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { return fDSP->metadata(m); }
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
       
};

/**
 * On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
 * flags to avoid costly denormals.
 */

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif

#ifndef __visEffect__
#define __visEffect__

// tags used by the Faust compiler to paste the generated c++ code
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  


#ifndef FAUSTCLASS 
#define FAUSTCLASS visEffect
#endif

class visEffect : public dsp {
  private:
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	float 	fConst3;
	float 	fConst4;
	float 	fConst5;
	float 	fConst6;
	float 	fConst7;
	float 	fConst8;
	float 	fConst9;
	float 	fConst10;
	float 	fConst11;
	float 	fRec11[2];
	int 	IOTA;
	float 	fVec0[8192];
	float 	fConst12;
	int 	iConst13;
	float 	fConst14;
	float 	fConst15;
	float 	fConst16;
	float 	fConst17;
	float 	fConst18;
	float 	fConst19;
	float 	fConst20;
	float 	fConst21;
	float 	fConst22;
	float 	fConst23;
	float 	fConst24;
	float 	fConst25;
	float 	fConst26;
	float 	fConst27;
	float 	fConst28;
	float 	fConst29;
	float 	fConst30;
	float 	fConst31;
	float 	fConst32;
	float 	fConst33;
	float 	fConst34;
	float 	fConst35;
	float 	fConst36;
	float 	fConst37;
	float 	fConst38;
	float 	fConst39;
	float 	fConst40;
	float 	fConst41;
	float 	fConst42;
	float 	fRec13[5];
	float 	fConst43;
	float 	fConst44;
	float 	fConst45;
	float 	fConst46;
	float 	fConst47;
	float 	fConst48;
	float 	fRec12[5];
	float 	fVec1[256];
	int 	iConst49;
	float 	fVec2[1024];
	int 	iConst50;
	float 	fRec9[2];
	float 	fConst51;
	float 	fConst52;
	float 	fConst53;
	float 	fConst54;
	float 	fConst55;
	float 	fConst56;
	float 	fConst57;
	float 	fConst58;
	float 	fConst59;
	float 	fRec16[2];
	float 	fVec3[8192];
	float 	fConst60;
	int 	iConst61;
	float 	fVec4[1024];
	int 	iConst62;
	float 	fRec14[2];
	float 	fConst63;
	float 	fConst64;
	float 	fConst65;
	float 	fConst66;
	float 	fConst67;
	float 	fConst68;
	float 	fConst69;
	float 	fConst70;
	float 	fConst71;
	float 	fRec19[2];
	float 	fVec5[8192];
	float 	fConst72;
	int 	iConst73;
	float 	fVec6[2048];
	int 	iConst74;
	float 	fRec17[2];
	float 	fConst75;
	float 	fConst76;
	float 	fConst77;
	float 	fConst78;
	float 	fConst79;
	float 	fConst80;
	float 	fConst81;
	float 	fConst82;
	float 	fConst83;
	float 	fRec22[2];
	float 	fVec7[8192];
	float 	fConst84;
	int 	iConst85;
	float 	fVec8[1024];
	int 	iConst86;
	float 	fRec20[2];
	float 	fConst87;
	float 	fConst88;
	float 	fConst89;
	float 	fConst90;
	float 	fConst91;
	float 	fConst92;
	float 	fConst93;
	float 	fConst94;
	float 	fConst95;
	float 	fRec25[2];
	float 	fVec9[16384];
	float 	fConst96;
	int 	iConst97;
	float 	fRec27[5];
	float 	fRec26[5];
	float 	fVec10[256];
	float 	fVec11[2048];
	int 	iConst98;
	float 	fRec23[2];
	float 	fConst99;
	float 	fConst100;
	float 	fConst101;
	float 	fConst102;
	float 	fConst103;
	float 	fConst104;
	float 	fConst105;
	float 	fConst106;
	float 	fConst107;
	float 	fRec30[2];
	float 	fVec12[8192];
	float 	fConst108;
	int 	iConst109;
	float 	fVec13[2048];
	int 	iConst110;
	float 	fRec28[2];
	float 	fConst111;
	float 	fConst112;
	float 	fConst113;
	float 	fConst114;
	float 	fConst115;
	float 	fConst116;
	float 	fConst117;
	float 	fConst118;
	float 	fConst119;
	float 	fRec33[2];
	float 	fVec14[16384];
	float 	fConst120;
	int 	iConst121;
	float 	fVec15[2048];
	int 	iConst122;
	float 	fRec31[2];
	float 	fConst123;
	float 	fConst124;
	float 	fConst125;
	float 	fConst126;
	float 	fConst127;
	float 	fConst128;
	float 	fConst129;
	float 	fConst130;
	float 	fConst131;
	float 	fRec36[2];
	float 	fVec16[16384];
	float 	fConst132;
	int 	iConst133;
	float 	fVec17[1024];
	int 	iConst134;
	float 	fRec34[2];
	float 	fRec1[2];
	float 	fRec2[2];
	float 	fRec3[2];
	float 	fRec4[2];
	float 	fRec5[2];
	float 	fRec6[2];
	float 	fRec7[2];
	float 	fRec8[2];
	float 	fConst135;
	float 	fConst136;
	float 	fConst137;
	float 	fConst138;
	float 	fRec39[2];
	float 	fRec38[2];
	float 	fRec37[2];
	float 	fVec18[2];
	float 	fRec0[2];
	float 	fRec43[2];
	float 	fRec42[2];
	float 	fRec41[2];
	float 	fVec19[2];
	float 	fRec40[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("reverb.lib/name", "Faust Reverb Library");
		m->declare("reverb.lib/version", "0.0");
		m->declare("compressor.lib/name", "Faust Compressor Effect Library");
		m->declare("compressor.lib/version", "0.0");
		m->declare("math.lib/name", "Faust Math Library");
		m->declare("math.lib/version", "2.0");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("delay.lib/name", "Faust Delay Library");
		m->declare("delay.lib/version", "0.0");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/version", "2.0");
		m->declare("route.lib/name", "Faust Signal Routing Library");
		m->declare("route.lib/version", "0.0");
		m->declare("signal.lib/name", "Faust Signal Routing Library");
		m->declare("signal.lib/version", "0.0");
		m->declare("basic.lib/name", "Faust Basic Element Library");
		m->declare("basic.lib/version", "0.0");
		m->declare("analyzer.lib/name", "Faust Analyzer Library");
		m->declare("analyzer.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 2; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(1.92e+05f, max(1.0f, (float)fSamplingFreq));
		fConst1 = floorf(((0.153129f * fConst0) + 0.5f));
		fConst2 = expf((0.1f * ((0 - (6.9077554f * fConst1)) / fConst0)));
		fConst3 = float(fConst0);
		fConst4 = cosf((37699.113f / fConst3));
		fConst5 = faustpower<2>(fConst2);
		fConst6 = (1.0f - (fConst4 * fConst5));
		fConst7 = (1.0f - fConst5);
		fConst8 = sqrtf(max((float)0, ((faustpower<2>(fConst6) / faustpower<2>(fConst7)) + -1.0f)));
		fConst9 = (fConst6 / fConst7);
		fConst10 = (fConst2 * (fConst8 + (1.0f - fConst9)));
		fConst11 = (fConst9 - fConst8);
		fConst12 = floorf(((0.020346f * fConst0) + 0.5f));
		iConst13 = int((int((fConst1 - fConst12)) & 8191));
		fConst14 = (1.0f / fConst3);
		fConst15 = faustpower<2>(fConst14);
		fConst16 = tanf((2827.4333f / fConst0));
		fConst17 = faustpower<2>(sqrtf((4.0f * ((faustpower<2>(fConst0) * fConst16) * tanf((628.31854f / fConst0))))));
		fConst18 = (fConst17 / fConst3);
		fConst19 = (fConst0 * fConst16);
		fConst20 = ((2.0f * fConst19) - (0.5f * (fConst17 / fConst19)));
		fConst21 = (1.5307337f * fConst20);
		fConst22 = faustpower<2>(fConst20);
		fConst23 = (4 * fConst22);
		fConst24 = (fConst20 / fConst3);
		fConst25 = (6.122935f * fConst24);
		fConst26 = ((((((((fConst18 + fConst21) / fConst3) + 8) * fConst17) + fConst23) * fConst15) + fConst25) + 16);
		fConst27 = (0.3f * (fConst15 / fConst26));
		fConst28 = (8 * fConst22);
		fConst29 = (0 - fConst28);
		fConst30 = (3.695518f * fConst20);
		fConst31 = (14.782072f * fConst24);
		fConst32 = ((((((((fConst18 + fConst30) / fConst3) + 8) * fConst17) + fConst23) * fConst15) + fConst31) + 16);
		fConst33 = (fConst15 / fConst32);
		fConst34 = (1.0f / fConst32);
		fConst35 = ((((((6 * (fConst17 * fConst15)) + -16) * fConst17) - fConst28) * fConst15) + 96);
		fConst36 = (4 * fConst18);
		fConst37 = (7.391036f * fConst20);
		fConst38 = faustpower<3>(fConst14);
		fConst39 = (29.564144f * fConst24);
		fConst40 = ((((fConst36 + fConst37) * fConst17) * fConst38) + (-64 - fConst39));
		fConst41 = (((((fConst36 - fConst37) * fConst17) * fConst38) + fConst39) + -64);
		fConst42 = (((((((fConst18 - fConst30) / fConst3) + 8) * fConst17) + fConst23) * fConst15) + (16 - fConst31));
		fConst43 = (1.0f / fConst26);
		fConst44 = (3.0614674f * fConst20);
		fConst45 = (12.24587f * fConst24);
		fConst46 = ((((fConst36 + fConst44) * fConst17) * fConst38) + (-64 - fConst45));
		fConst47 = (((((fConst36 - fConst44) * fConst17) * fConst38) + fConst45) + -64);
		fConst48 = (((((((fConst18 - fConst21) / fConst3) + 8) * fConst17) + fConst23) * fConst15) + (16 - fConst25));
		iConst49 = int((int((0.001f * fConst0)) & 8191));
		iConst50 = int((int((fConst12 + -1)) & 1023));
		fConst51 = floorf(((0.174713f * fConst0) + 0.5f));
		fConst52 = expf((0.1f * ((0 - (6.9077554f * fConst51)) / fConst0)));
		fConst53 = faustpower<2>(fConst52);
		fConst54 = (1.0f - (fConst4 * fConst53));
		fConst55 = (1.0f - fConst53);
		fConst56 = sqrtf(max((float)0, ((faustpower<2>(fConst54) / faustpower<2>(fConst55)) + -1.0f)));
		fConst57 = (fConst54 / fConst55);
		fConst58 = (fConst52 * (fConst56 + (1.0f - fConst57)));
		fConst59 = (fConst57 - fConst56);
		fConst60 = floorf(((0.022904f * fConst0) + 0.5f));
		iConst61 = int((int((fConst51 - fConst60)) & 8191));
		iConst62 = int((int((fConst60 + -1)) & 1023));
		fConst63 = floorf(((0.127837f * fConst0) + 0.5f));
		fConst64 = expf((0.1f * ((0 - (6.9077554f * fConst63)) / fConst0)));
		fConst65 = faustpower<2>(fConst64);
		fConst66 = (1.0f - (fConst4 * fConst65));
		fConst67 = (1.0f - fConst65);
		fConst68 = sqrtf(max((float)0, ((faustpower<2>(fConst66) / faustpower<2>(fConst67)) + -1.0f)));
		fConst69 = (fConst66 / fConst67);
		fConst70 = (fConst64 * (fConst68 + (1.0f - fConst69)));
		fConst71 = (fConst69 - fConst68);
		fConst72 = floorf(((0.031604f * fConst0) + 0.5f));
		iConst73 = int((int((fConst63 - fConst72)) & 8191));
		iConst74 = int((int((fConst72 + -1)) & 2047));
		fConst75 = floorf(((0.125f * fConst0) + 0.5f));
		fConst76 = expf((0.1f * ((0 - (6.9077554f * fConst75)) / fConst0)));
		fConst77 = faustpower<2>(fConst76);
		fConst78 = (1.0f - (fConst4 * fConst77));
		fConst79 = (1.0f - fConst77);
		fConst80 = sqrtf(max((float)0, ((faustpower<2>(fConst78) / faustpower<2>(fConst79)) + -1.0f)));
		fConst81 = (fConst78 / fConst79);
		fConst82 = (fConst76 * (fConst80 + (1.0f - fConst81)));
		fConst83 = (fConst81 - fConst80);
		fConst84 = floorf(((0.013458f * fConst0) + 0.5f));
		iConst85 = int((int((fConst75 - fConst84)) & 8191));
		iConst86 = int((int((fConst84 + -1)) & 1023));
		fConst87 = floorf(((0.210389f * fConst0) + 0.5f));
		fConst88 = expf((0.1f * ((0 - (6.9077554f * fConst87)) / fConst0)));
		fConst89 = faustpower<2>(fConst88);
		fConst90 = (1.0f - (fConst4 * fConst89));
		fConst91 = (1.0f - fConst89);
		fConst92 = sqrtf(max((float)0, ((faustpower<2>(fConst90) / faustpower<2>(fConst91)) + -1.0f)));
		fConst93 = (fConst90 / fConst91);
		fConst94 = (fConst88 * (fConst92 + (1.0f - fConst93)));
		fConst95 = (fConst93 - fConst92);
		fConst96 = floorf(((0.024421f * fConst0) + 0.5f));
		iConst97 = int((int((fConst87 - fConst96)) & 16383));
		iConst98 = int((int((fConst96 + -1)) & 2047));
		fConst99 = floorf(((0.192303f * fConst0) + 0.5f));
		fConst100 = expf((0.1f * ((0 - (6.9077554f * fConst99)) / fConst0)));
		fConst101 = faustpower<2>(fConst100);
		fConst102 = (1.0f - (fConst4 * fConst101));
		fConst103 = (1.0f - fConst101);
		fConst104 = sqrtf(max((float)0, ((faustpower<2>(fConst102) / faustpower<2>(fConst103)) + -1.0f)));
		fConst105 = (fConst102 / fConst103);
		fConst106 = (fConst100 * (fConst104 + (1.0f - fConst105)));
		fConst107 = (fConst105 - fConst104);
		fConst108 = floorf(((0.029291f * fConst0) + 0.5f));
		iConst109 = int((int((fConst99 - fConst108)) & 8191));
		iConst110 = int((int((fConst108 + -1)) & 2047));
		fConst111 = floorf(((0.256891f * fConst0) + 0.5f));
		fConst112 = expf((0.1f * ((0 - (6.9077554f * fConst111)) / fConst0)));
		fConst113 = faustpower<2>(fConst112);
		fConst114 = (1.0f - (fConst4 * fConst113));
		fConst115 = (1.0f - fConst113);
		fConst116 = sqrtf(max((float)0, ((faustpower<2>(fConst114) / faustpower<2>(fConst115)) + -1.0f)));
		fConst117 = (fConst114 / fConst115);
		fConst118 = (fConst112 * (fConst116 + (1.0f - fConst117)));
		fConst119 = (fConst117 - fConst116);
		fConst120 = floorf(((0.027333f * fConst0) + 0.5f));
		iConst121 = int((int((fConst111 - fConst120)) & 16383));
		iConst122 = int((int((fConst120 + -1)) & 2047));
		fConst123 = floorf(((0.219991f * fConst0) + 0.5f));
		fConst124 = expf((0.1f * ((0 - (6.9077554f * fConst123)) / fConst0)));
		fConst125 = faustpower<2>(fConst124);
		fConst126 = (1.0f - (fConst125 * fConst4));
		fConst127 = (1.0f - fConst125);
		fConst128 = sqrtf(max((float)0, ((faustpower<2>(fConst126) / faustpower<2>(fConst127)) + -1.0f)));
		fConst129 = (fConst126 / fConst127);
		fConst130 = (fConst124 * (fConst128 + (1.0f - fConst129)));
		fConst131 = (fConst129 - fConst128);
		fConst132 = floorf(((0.019123f * fConst0) + 0.5f));
		iConst133 = int((int((fConst123 - fConst132)) & 16383));
		iConst134 = int((int((fConst132 + -1)) & 1023));
		fConst135 = expf((0 - (1e+03f / fConst0)));
		fConst136 = (1.0f - fConst135);
		fConst137 = expf((0 - (2.5f / fConst0)));
		fConst138 = expf((0 - (5e+02f / fConst0)));
	}
	virtual void instanceResetUserInterface() {
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec11[i] = 0;
		IOTA = 0;
		for (int i=0; i<8192; i++) fVec0[i] = 0;
		for (int i=0; i<5; i++) fRec13[i] = 0;
		for (int i=0; i<5; i++) fRec12[i] = 0;
		for (int i=0; i<256; i++) fVec1[i] = 0;
		for (int i=0; i<1024; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<8192; i++) fVec3[i] = 0;
		for (int i=0; i<1024; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<8192; i++) fVec5[i] = 0;
		for (int i=0; i<2048; i++) fVec6[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<8192; i++) fVec7[i] = 0;
		for (int i=0; i<1024; i++) fVec8[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<16384; i++) fVec9[i] = 0;
		for (int i=0; i<5; i++) fRec27[i] = 0;
		for (int i=0; i<5; i++) fRec26[i] = 0;
		for (int i=0; i<256; i++) fVec10[i] = 0;
		for (int i=0; i<2048; i++) fVec11[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<8192; i++) fVec12[i] = 0;
		for (int i=0; i<2048; i++) fVec13[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<2; i++) fRec33[i] = 0;
		for (int i=0; i<16384; i++) fVec14[i] = 0;
		for (int i=0; i<2048; i++) fVec15[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<16384; i++) fVec16[i] = 0;
		for (int i=0; i<1024; i++) fVec17[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec39[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<2; i++) fVec18[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec43[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<2; i++) fRec41[i] = 0;
		for (int i=0; i<2; i++) fVec19[i] = 0;
		for (int i=0; i<2; i++) fRec40[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	virtual visEffect* clone() {
		return new visEffect();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("0x00");
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		for (int i=0; i<count; i++) {
			fRec11[0] = ((fConst10 * fRec1[1]) + (fConst11 * fRec11[1]));
			fVec0[IOTA&8191] = ((0.35355338f * fRec11[0]) + 1e-20f);
			fRec13[0] = ((float)input0[i] - (fConst34 * ((((fConst35 * fRec13[2]) + (fConst40 * fRec13[1])) + (fConst41 * fRec13[3])) + (fConst42 * fRec13[4]))));
			fRec12[0] = ((fConst33 * ((fConst29 * fRec13[2]) + (fConst23 * (fRec13[4] + fRec13[0])))) - (fConst43 * ((((fConst35 * fRec12[2]) + (fConst46 * fRec12[1])) + (fConst47 * fRec12[3])) + (fConst48 * fRec12[4]))));
			fVec1[IOTA&255] = ((fConst29 * fRec12[2]) + (fConst23 * (fRec12[4] + fRec12[0])));
			float fTemp0 = (fConst27 * fVec1[(IOTA-iConst49)&255]);
			float fTemp1 = ((fVec0[(IOTA-iConst13)&8191] + fTemp0) - (0.6f * fRec9[1]));
			fVec2[IOTA&1023] = fTemp1;
			fRec9[0] = fVec2[(IOTA-iConst50)&1023];
			float 	fRec10 = (0.6f * fVec2[IOTA&1023]);
			fRec16[0] = ((fConst58 * fRec5[1]) + (fConst59 * fRec16[1]));
			fVec3[IOTA&8191] = ((0.35355338f * fRec16[0]) + 1e-20f);
			float fTemp2 = ((fVec3[(IOTA-iConst61)&8191] + fTemp0) - (0.6f * fRec14[1]));
			fVec4[IOTA&1023] = fTemp2;
			fRec14[0] = fVec4[(IOTA-iConst62)&1023];
			float 	fRec15 = (0.6f * fVec4[IOTA&1023]);
			fRec19[0] = ((fConst70 * fRec3[1]) + (fConst71 * fRec19[1]));
			fVec5[IOTA&8191] = ((0.35355338f * fRec19[0]) + 1e-20f);
			float fTemp3 = (fVec5[(IOTA-iConst73)&8191] - ((0.6f * fRec17[1]) + fTemp0));
			fVec6[IOTA&2047] = fTemp3;
			fRec17[0] = fVec6[(IOTA-iConst74)&2047];
			float 	fRec18 = (0.6f * fVec6[IOTA&2047]);
			fRec22[0] = ((fConst82 * fRec7[1]) + (fConst83 * fRec22[1]));
			fVec7[IOTA&8191] = ((0.35355338f * fRec22[0]) + 1e-20f);
			float fTemp4 = (fVec7[(IOTA-iConst85)&8191] - ((0.6f * fRec20[1]) + fTemp0));
			fVec8[IOTA&1023] = fTemp4;
			fRec20[0] = fVec8[(IOTA-iConst86)&1023];
			float 	fRec21 = (0.6f * fVec8[IOTA&1023]);
			fRec25[0] = ((fConst94 * fRec2[1]) + (fConst95 * fRec25[1]));
			fVec9[IOTA&16383] = ((0.35355338f * fRec25[0]) + 1e-20f);
			fRec27[0] = ((float)input1[i] - (fConst34 * ((((fConst35 * fRec27[2]) + (fConst40 * fRec27[1])) + (fConst41 * fRec27[3])) + (fConst42 * fRec27[4]))));
			fRec26[0] = ((fConst33 * ((fConst29 * fRec27[2]) + (fConst23 * (fRec27[4] + fRec27[0])))) - (fConst43 * ((((fConst35 * fRec26[2]) + (fConst46 * fRec26[1])) + (fConst47 * fRec26[3])) + (fConst48 * fRec26[4]))));
			fVec10[IOTA&255] = ((fConst29 * fRec26[2]) + (fConst23 * (fRec26[4] + fRec26[0])));
			float fTemp5 = (fConst27 * fVec10[(IOTA-iConst49)&255]);
			float fTemp6 = (((0.6f * fRec23[1]) + fVec9[(IOTA-iConst97)&16383]) + fTemp5);
			fVec11[IOTA&2047] = fTemp6;
			fRec23[0] = fVec11[(IOTA-iConst98)&2047];
			float 	fRec24 = (0 - (0.6f * fVec11[IOTA&2047]));
			fRec30[0] = ((fConst106 * fRec6[1]) + (fConst107 * fRec30[1]));
			fVec12[IOTA&8191] = ((0.35355338f * fRec30[0]) + 1e-20f);
			float fTemp7 = (fTemp5 + ((0.6f * fRec28[1]) + fVec12[(IOTA-iConst109)&8191]));
			fVec13[IOTA&2047] = fTemp7;
			fRec28[0] = fVec13[(IOTA-iConst110)&2047];
			float 	fRec29 = (0 - (0.6f * fVec13[IOTA&2047]));
			fRec33[0] = ((fConst118 * fRec4[1]) + (fConst119 * fRec33[1]));
			fVec14[IOTA&16383] = ((0.35355338f * fRec33[0]) + 1e-20f);
			float fTemp8 = (((0.6f * fRec31[1]) + fVec14[(IOTA-iConst121)&16383]) - fTemp5);
			fVec15[IOTA&2047] = fTemp8;
			fRec31[0] = fVec15[(IOTA-iConst122)&2047];
			float 	fRec32 = (0 - (0.6f * fVec15[IOTA&2047]));
			fRec36[0] = ((fConst130 * fRec8[1]) + (fConst131 * fRec36[1]));
			fVec16[IOTA&16383] = ((0.35355338f * fRec36[0]) + 1e-20f);
			float fTemp9 = (((0.6f * fRec34[1]) + fVec16[(IOTA-iConst133)&16383]) - fTemp5);
			fVec17[IOTA&1023] = fTemp9;
			fRec34[0] = fVec17[(IOTA-iConst134)&1023];
			float 	fRec35 = (0 - (0.6f * fVec17[IOTA&1023]));
			float fTemp10 = (fRec34[1] + fRec35);
			float fTemp11 = (fRec32 + (fRec31[1] + fTemp10));
			float fTemp12 = (fRec24 + (fRec23[1] + (fRec29 + (fRec28[1] + fTemp11))));
			fRec1[0] = (fRec10 + (fRec9[1] + (fRec15 + (fRec14[1] + (fRec18 + (fRec17[1] + (fRec21 + (fRec20[1] + fTemp12))))))));
			fRec2[0] = ((fRec10 + (fRec9[1] + (fRec15 + (fRec14[1] + (fRec18 + (fRec17[1] + (fRec20[1] + fRec21))))))) - fTemp12);
			float fTemp13 = (fRec24 + (fRec23[1] + (fRec28[1] + fRec29)));
			fRec3[0] = ((fRec10 + (fRec9[1] + (fRec15 + (fRec14[1] + fTemp13)))) - (fRec18 + (fRec17[1] + (fRec21 + (fRec20[1] + fTemp11)))));
			fRec4[0] = ((fRec10 + (fRec9[1] + (fRec15 + (fRec14[1] + fTemp11)))) - (fRec18 + (fRec17[1] + (fRec21 + (fRec20[1] + fTemp13)))));
			float fTemp14 = (fRec31[1] + fRec32);
			float fTemp15 = (fRec24 + (fRec23[1] + fTemp14));
			float fTemp16 = (fRec29 + (fRec28[1] + fTemp10));
			fRec5[0] = ((fRec10 + (fRec9[1] + (fRec18 + (fRec17[1] + fTemp15)))) - (fRec15 + (fRec14[1] + (fRec21 + (fRec20[1] + fTemp16)))));
			fRec6[0] = ((fRec10 + (fRec9[1] + (fRec18 + (fRec17[1] + fTemp16)))) - (fRec15 + (fRec14[1] + (fRec21 + (fRec20[1] + fTemp15)))));
			float fTemp17 = (fRec24 + (fRec23[1] + fTemp10));
			float fTemp18 = (fRec29 + (fRec28[1] + fTemp14));
			fRec7[0] = ((fRec10 + (fRec9[1] + (fRec21 + (fRec20[1] + fTemp17)))) - (fRec15 + (fRec14[1] + (fRec18 + (fRec17[1] + fTemp18)))));
			fRec8[0] = ((fRec10 + (fRec9[1] + (fRec21 + (fRec20[1] + fTemp18)))) - (fRec15 + (fRec14[1] + (fRec18 + (fRec17[1] + fTemp17)))));
			float fTemp19 = (fRec2[0] + fRec3[0]);
			float fTemp20 = fabsf((0.37f * fTemp19));
			float fTemp21 = ((int((fRec38[1] > fTemp20)))?fConst137:fConst138);
			fRec39[0] = ((fTemp20 * (1.0f - fTemp21)) + (fRec39[1] * fTemp21));
			fRec38[0] = fRec39[0];
			fRec37[0] = ((fConst135 * fRec37[1]) + (fConst136 * (0 - (0.8f * max(((20 * log10f(fRec38[0])) + 30), 0.0f)))));
			float fTemp22 = (fTemp19 * powf(10,(0.05f * fRec37[0])));
			fVec18[0] = fTemp22;
			fRec0[0] = ((0.995f * fRec0[1]) + (0.555f * (fVec18[0] - fVec18[1])));
			output0[i] = (FAUSTFLOAT)fRec0[0];
			float fTemp23 = (fRec2[0] - fRec3[0]);
			float fTemp24 = fabsf((0.37f * fTemp23));
			float fTemp25 = ((int((fRec42[1] > fTemp24)))?fConst137:fConst138);
			fRec43[0] = ((fTemp24 * (1.0f - fTemp25)) + (fRec43[1] * fTemp25));
			fRec42[0] = fRec43[0];
			fRec41[0] = ((fConst135 * fRec41[1]) + (fConst136 * (0 - (0.8f * max(((20 * log10f(fRec42[0])) + 30), 0.0f)))));
			float fTemp26 = (fTemp23 * powf(10,(0.05f * fRec41[0])));
			fVec19[0] = fTemp26;
			fRec40[0] = ((0.995f * fRec40[1]) + (0.555f * (fVec19[0] - fVec19[1])));
			output1[i] = (FAUSTFLOAT)fRec40[0];
			// post processing
			fRec40[1] = fRec40[0];
			fVec19[1] = fVec19[0];
			fRec41[1] = fRec41[0];
			fRec42[1] = fRec42[0];
			fRec43[1] = fRec43[0];
			fRec0[1] = fRec0[0];
			fVec18[1] = fVec18[0];
			fRec37[1] = fRec37[0];
			fRec38[1] = fRec38[0];
			fRec39[1] = fRec39[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec34[1] = fRec34[0];
			fRec36[1] = fRec36[0];
			fRec31[1] = fRec31[0];
			fRec33[1] = fRec33[0];
			fRec28[1] = fRec28[0];
			fRec30[1] = fRec30[0];
			fRec23[1] = fRec23[0];
			for (int i=4; i>0; i--) fRec26[i] = fRec26[i-1];
			for (int i=4; i>0; i--) fRec27[i] = fRec27[i-1];
			fRec25[1] = fRec25[0];
			fRec20[1] = fRec20[0];
			fRec22[1] = fRec22[0];
			fRec17[1] = fRec17[0];
			fRec19[1] = fRec19[0];
			fRec14[1] = fRec14[0];
			fRec16[1] = fRec16[0];
			fRec9[1] = fRec9[0];
			for (int i=4; i>0; i--) fRec12[i] = fRec12[i-1];
			for (int i=4; i>0; i--) fRec13[i] = fRec13[i-1];
			IOTA = IOTA+1;
			fRec11[1] = fRec11[0];
		}
	}
};


#endif
