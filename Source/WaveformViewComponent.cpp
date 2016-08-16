#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveformViewComponent.h"

WaveformViewComponent::WaveformViewComponent() {
    setSize(360, 300);
    lines.resize(512);
};

WaveformViewComponent::~WaveformViewComponent() {
    
};

void WaveformViewComponent::paint(Graphics& g) {
    g.fillAll(Colours::lightskyblue);

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

void WaveformViewComponent::thumbnailChanged() {
    repaint();
}

void WaveformViewComponent::transportSourceChanged() {
}

void WaveformViewComponent::changeListenerCallback(ChangeBroadcaster * source) {
    //if (source == &m_source) transportSourceChanged();
    //if (source == &thumbnail) thumbnailChanged();
}

void WaveformViewComponent::fillBuffer(float *buffer, int len) {
    m_locked = true;
    lines.clear();

    int pos = 0;
    int scale = 100.0;
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

void WaveformViewComponent::setBufferSize(unsigned int len) {
    //lines.resize(len);
}

