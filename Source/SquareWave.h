#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "IWave.h"

class SquareWave : public IWave
{
public:
    SquareWave() {};
    ~SquareWave() {};
    
    double sample(double t, int len) override {      
        return level * sampleByTime(t);
        //return level * sampleBySinSign(t);
    };

    double sampleByTime(double t) {
        double fullPeriodTime = 1.0 / frequency;
        double halfPeriodTime = fullPeriodTime / 2.0;
        double localTime = fmod(t, fullPeriodTime);

        if (localTime < halfPeriodTime) return 1.0;
        else return -1.0;
    }

    double sampleBySinSign(double t) {
        return sign(sin(2 * double_Pi * frequency * t + phase));
    }

    int sign(double value) { return (value >= 0.0) ? 1 : -1; }
};

