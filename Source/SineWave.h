#pragma once

#include <math.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "juce_core\maths\juce_MathsFunctions.h"

class SineWave
{
public:
    SineWave();
    ~SineWave();

    void setParams(double amplitude, double freq, double phase);
    double nextSample(double t);

    void setAmplitude(double value) { m_amplitude = value; };
    void setFrequency(double value) { m_frequency = value; };
    void setPhase(double value) { m_phase = value; };

    double getAmplitude() { return m_amplitude; }

    void mute() { m_mute = true; }
    void unmute() { m_mute = false; }
    bool isMuted() { return m_mute; }
private:
    double m_amplitude;
    double m_frequency;
    double m_phase;

    bool m_mute = false;
};

