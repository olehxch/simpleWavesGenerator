#pragma once

#include <math.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "juce_core\maths\juce_MathsFunctions.h"
#include "IWave.h"

class WhiteNoise : public IWave
{
public:
    WhiteNoise() {};
    ~WhiteNoise() {};

    double sample(double t, int len) override {
        return m_level * random.nextDouble();
    };

private:
    Random random;
};

