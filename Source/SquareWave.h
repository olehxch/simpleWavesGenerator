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
    
    double sample(double t, int len) override {      
        return m_level * sampleByTime(t);
        //return m_level * sampleBySinSign(t);
    };

    double sampleByTime(double t) {
        double fullPeriodTime = 1.0 / m_frequency;
        double halfPeriodTime = fullPeriodTime / 2.0;
        double localTime = fmod(t, fullPeriodTime);

        if (localTime < halfPeriodTime) return 1.0;
        else return -1.0;
    }

    double sampleBySinSign(double t) {
        return sign(sin(2 * double_Pi * m_frequency * t + m_phase));
    }

    int sign(double value) { return (value >= 0.0) ? 1 : -1; }
};

