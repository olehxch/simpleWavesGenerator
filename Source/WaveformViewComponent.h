#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <vector>

class WaveformViewComponent : public Component, public ChangeListener
{
public:
    WaveformViewComponent();
    ~WaveformViewComponent();

    void paint(Graphics& g) override;

    void resized();
    void thumbnailChanged();
    void transportSourceChanged();

    void changeListenerCallback(ChangeBroadcaster* source) override;

    void fillBuffer(float *buffer, int len);

    void setBufferSize(unsigned int len);
private:
    std::vector< Line<float> > lines;

    // prevents drawing when buffer is updating with new data
    bool m_locked = true;
    int m_width;
    int m_height;
};

