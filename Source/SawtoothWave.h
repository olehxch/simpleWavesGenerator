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
    
    double sample(double t) {
        return m_level * 0.0;
    };

    int sign(double value) { return (value >= 0.0) ? 1 : -1; }
};

