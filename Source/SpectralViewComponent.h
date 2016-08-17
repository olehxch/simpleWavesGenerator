#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <vector>
#include <algorithm>

class SpectralViewComponent : public Component
{
public:
    SpectralViewComponent();
    ~SpectralViewComponent();

    void paint(Graphics& g) override;

    void resized();
    void fillBuffer(float *buffer, int len);
private:
    float findmax(float* buf, int len);

    int m_width;
    int m_height;

    // prevents drawing when buffer is updating with new data
    bool m_locked = true;

    std::vector< Line<float> > lines;
};

