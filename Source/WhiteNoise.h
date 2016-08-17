#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "IWave.h"

class WhiteNoise : public IWave
{
public:
    WhiteNoise() {};
    ~WhiteNoise() {};

    double sample(double t, int len) override {
        return level * random.nextDouble();
    };

private:
    Random random;
};

