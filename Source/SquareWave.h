#pragma once

#include <math.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "juce_core\maths\juce_MathsFunctions.h"
#include "IWave.h"

class SquareWave : public IWave
{
public:
    SquareWave() {};
    ~SquareWave() {};
    
    double sample(double t) override {
        //double step = 1.0 / 44100;

        //double freqStep = 1.0 / m_frequency;
        //double halfStep = freqStep / 2.0;
        

        return m_level * sign(sin(2 * double_Pi * m_frequency * t + m_phase));
    };

    int sign(double value) { return (value >= 0.0) ? 1 : -1; }
};

