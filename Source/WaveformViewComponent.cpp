#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveformViewComponent.h"

WaveformViewComponent::WaveformViewComponent() {
    setSize(360, 300);
    lines.resize(512);

    m_width = getBounds().getWidth();
    m_height = getBounds().getHeight();
};

WaveformViewComponent::~WaveformViewComponent() {
};

void WaveformViewComponent::paint(Graphics& g) {
    g.fillAll(Colour::fromRGB(0xF1, 0xF0, 0xFE));

    //g.drawRect(0, 0, m_width, m_height, 1.0);
    g.drawLine(0, m_height, m_width, m_height);
    g.drawText("Oscilloscope", 0, 5, m_width, 10, Justification::centred);


    g.setColour(Colour::fromRGB(0x2B, 0x2C, 0x43)); // #2B2C43
    if (!m_locked) {
        std::vector<Line<float> > copyLines(lines);
        for (auto line : copyLines) {
            g.drawLine(line);
        }
    }
}

void WaveformViewComponent::resized() {
    repaint();
}

void WaveformViewComponent::fillBuffer(float *buffer, int len) {
    m_locked = true;
    lines.clear();

    int pos = 0;
    int scale = 200.0;
    for (int i = 0; i < len - 1; i++) {
        float cur = buffer[i] * scale;
        float next = buffer[i + 1] * scale;

        Line<float> l;
        l.setStart(pos++, cur + 150);
        l.setEnd(pos, next + 150);
        lines.push_back(l);
    }

    m_locked = false;
}
