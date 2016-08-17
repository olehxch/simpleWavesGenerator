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

    if (!m_locked) {
        g.setColour(Colour::fromRGB(0x2B, 0x2C, 0x43)); // set line color
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

    const int fftBufferSize = juce::nextPowerOfTwo(len);
    int powerOfTwo = log(fftBufferSize) / log(2);
    int halfBuffer = fftBufferSize / 2;

    float* fftBuffer = new float[fftBufferSize] { 0 };
    memcpy(fftBuffer, buffer, len);

    FFT fft(powerOfTwo - 1, false);
    fft.performFrequencyOnlyForwardTransform(fftBuffer);
    lines.clear();
    
    float pos = 0;
    float scale = m_height / findmax(fftBuffer, 512);
    float step = m_width / 128.0;
    for (int i = 0; i < halfBuffer; i++) {
        float cur = fftBuffer[i] * scale;

        // check if cur is NaN
        if (cur != cur) cur = 0.0;

        Line<float> l;
        l.setStart(pos, m_height);
        l.setEnd(pos, m_height - cur);

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


