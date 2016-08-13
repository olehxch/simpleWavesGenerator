#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "juce_core\maths\juce_MathsFunctions.h"

class WhiteNoise
{
public:
    WhiteNoise();
    ~WhiteNoise();

    double nextSample();

    void setLevel(double value) { m_level = value; }
    double getLevel() { return m_level; }

    void mute() { m_mute = true; }
    void unmute() { m_mute = false; }
    bool isMuted() { return m_mute; }

private:
    Random random;
    bool m_mute = false;

    double m_level;
};

