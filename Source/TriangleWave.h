#pragma once

#include <math.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "juce_core\maths\juce_MathsFunctions.h"
#include "IWave.h"

class TriangleWave : public IWave
{
public:
    TriangleWave() {};
    ~TriangleWave() {};
    
    double sample(double t, int len) override {
        return m_level * sampleByTime(t);
    };

    double sampleByTime(double t) {
        double fullPeriodTime = 1.0 / m_frequency;
        double halfPeriodTime = fullPeriodTime / 2.0;
        double localTime = fmod(t, fullPeriodTime);

        double value = localTime / fullPeriodTime;

        if (value < 0.25) {
            return value * 4;
        }
        else if (value < 0.75) {
            return 2.0 - (value * 4.0);
        }
        else {
            return value * 4 - 4.0;
        }

    }
};

