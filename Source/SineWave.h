#pragma once

#include <math.h>
#include "IWave.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "juce_core\maths\juce_MathsFunctions.h"

class SineWave : public IWave
{
public:
    SineWave() {};
    ~SineWave() {};

    double sample(double t) override {
        return m_level * sin(2 * double_Pi * m_frequency * t + m_phase);
    };

};

