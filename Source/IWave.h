#pragma once

#include <math.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "juce_core\maths\juce_MathsFunctions.h"

class IWave
{
public:
    IWave() : m_level(0.0), m_frequency(0.0), m_phase(0.0) {};
    ~IWave() {};

    void setParams(double level, double freq, double phase) {
        m_level = level;
        m_frequency = freq;
        m_phase = phase;
    };

    double nextSample(double t) {
        if (m_mute) return 0.0;
        return sample(t);
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

protected:
    double m_level;
    double m_frequency;
    double m_phase;

    bool m_mute = false;

    /**
    * You should override this method
    */
    virtual double sample(double t) = 0;
};

