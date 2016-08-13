#include "SineWave.h"



SineWave::SineWave():
    m_amplitude(0.0),
    m_frequency(0.0),
    m_phase(0.0)
{
}


SineWave::~SineWave()
{
}

void SineWave::setParams(double amplitude, double freq, double phase)
{
    m_amplitude = amplitude;
    m_frequency = freq;
    m_phase = phase;
}

double SineWave::nextSample(double t)
{
    if (m_mute) return 0.0;

    return m_amplitude * sin(2 * double_Pi * m_frequency * t + m_phase);
}
