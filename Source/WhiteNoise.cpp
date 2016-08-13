#include "WhiteNoise.h"



WhiteNoise::WhiteNoise():
    m_level(0.0)
{
}


WhiteNoise::~WhiteNoise()
{
}

double WhiteNoise::nextSample()
{
    if (m_mute) return 0.0;

    return m_level * random.nextDouble();
}
