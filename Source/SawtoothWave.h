#pragma once

#include <math.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "juce_core\maths\juce_MathsFunctions.h"
#include "IWave.h"

class SawtoothWave : public IWave
{
public:
    SawtoothWave() {};
    ~SawtoothWave() {};
    
    double sample(double t, int len) {
        return m_level * sampleByTime(t);
    };

    double sampleByTime(double t) {
        double fullPeriodTime = 1.0 / m_frequency;
        double halfPeriodTime = fullPeriodTime / 2.0;
        double localTime = fmod(t, fullPeriodTime);

        double value = localTime / fullPeriodTime;

        return value * 2 - 1.0;
    }

};

