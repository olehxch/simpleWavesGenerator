#pragma once

#include <math.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "juce_core\maths\juce_MathsFunctions.h"

class IWave
{
public:
    IWave() : m_level(0.0), m_frequency(0.0), m_phase(0.0), bufferLen(441), sampleRate(44100.0) {};
    ~IWave() {};

    void setParams(double level, double freq, double phase) {
        m_level = level;
        m_frequency = freq;
        m_phase = phase;
    };

    double nextSample(double t, int len) {
        if (m_mute) return 0.0;
        return sample(t, len);
    };

    void setAmplitude(double value) { m_level = value; };
    void setFrequency(double value) { m_frequency = value; };
    void setPhase(double value) { m_phase = value; };

    double getAmplitude() { return m_level; }
    double getFrequency() { return m_frequency; }
    double getPhase() { return m_phase; }    

    void mute() { m_mute = true; }
    void unmute() { m_mute = false; }
    bool isMuted() { return m_mute; }

    void setBufferLen(int value) { bufferLen = value; }
    void setSampleRate(int value) { sampleRate = value; }

    
    void localTime(double t) {

    }
protected:
    double m_level;
    double m_frequency;
    double m_phase;

    int bufferLen;
    double sampleRate;
   
    bool m_mute = false;

    /**
    * You should override this method
    */
    virtual double sample(double t, int len) = 0;
};

