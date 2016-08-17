#pragma once

#include "IWave.h"
#include "../JuceLibraryCode/JuceHeader.h"

class SineWave : public IWave
{
public:
    SineWave() {};
    ~SineWave() {};

    double sample(double t, int len) override {
        return level * sin(2 * double_Pi * frequency * t + phase);
    };

};

