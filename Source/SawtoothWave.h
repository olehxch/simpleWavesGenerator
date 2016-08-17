#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "IWave.h"

class SawtoothWave : public IWave
{
public:
    SawtoothWave() {};
    ~SawtoothWave() {};
    
    double sample(double t, int len) {
        double fullPeriodTime = 1.0 / frequency;
        double localTime = fmod(t, fullPeriodTime);

        return level * ((localTime / fullPeriodTime) * 2 - 1.0);
    };

};

