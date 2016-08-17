#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SpectralViewComponent.h"

SpectralViewComponent::SpectralViewComponent() {
    setSize(360, 300);
    lines.resize(512);

    m_width = getBounds().getWidth();
    m_height = getBounds().getHeight();
};

SpectralViewComponent::~SpectralViewComponent() {
    
};

void SpectralViewComponent::paint(Graphics& g) {
    g.fillAll(Colour::fromRGB(0xF1, 0xF0, 0xFE) ); // #F1F0FE

    g.drawLine(0, 0, m_width, 0);
    g.drawText("Spectral View", 0, 5, m_width, 10, Justification::centred);

    g.setColour(Colour::fromRGB(0x2B, 0x2C, 0x43));
    if (!m_locked) {
        std::vector<Line<float> > copyLines(lines);
        for (auto line : copyLines) {
            g.drawLine(line, 2.8);
        }
    }
}

void SpectralViewComponent::resized() {
    repaint();
}


void SpectralViewComponent::fillBuffer(float *buffer, int len) {
    m_locked = true;

    float* buf2 = new float[512] { 0 };
    memcpy(buf2, buffer, len);

    FFT fft(8, false); // 256
    fft.performFrequencyOnlyForwardTransform(buf2);
    lines.clear();

    float maxelem = findmax(buf2, 512);
    
    float pos = 0;
    int width = getBounds().getWidth();
    int height = getBounds().getHeight();

    float scale = height / maxelem;
    float step = width / 128.0;
    for (int i = 0; i < 128; i++) {
        float cur = buf2[i] * scale;

        // check if cur is NaN
        if (cur != cur) cur = 0.0;

        Line<float> l;
        l.setStart(pos, height);
        l.setEnd(pos, height - cur);

        lines.push_back(l);

        pos += step;
    }

    m_locked = false;
}

float SpectralViewComponent::findmax(float * buf, int len)
{
    int i = len;
    float max = 0.0;
    while (i--) {
        if (buf[i] > max) max = buf[i];
    }

    return max;
}

