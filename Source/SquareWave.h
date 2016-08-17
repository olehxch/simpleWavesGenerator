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
        
        
        // harmonics
        double sum = 0.0;
        double level = m_level;

        double step = 1.0 / sampleRate;
        double period = step / bufferLen;

        for (int n = 0; n < period; n++) {
            sum += sin(2.0 * double_Pi*(2.0 * n + 1.0)*m_frequency*t) / (2.0 * n + 1.0);
        }

        /*for (int i = 0; i <= 100; i++) {
            double freq = m_frequency * 2;

            double value = sin(2 * double_Pi * freq * t + m_phase);

            sum += value;

            //level -= 0.02;
        }*/

        return m_level * sum;
        //return m_level * sign(sin(2 * double_Pi * m_frequency * t + m_phase));
    };

    int sign(double value) { return (value >= 0.0) ? 1 : -1; }
};

