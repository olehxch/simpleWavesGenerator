#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MIDIKeyboard : public Component //: public MidiKeyboardComponent
                        //private MidiInputCallback,
                        //private MidiKeyboardStateListener
{
public:
    MIDIKeyboard(): m_keyboard(state, MidiKeyboardComponent::horizontalKeyboard) {
        addAndMakeVisible(m_keyboard);
    }

    ~MIDIKeyboard() {};

    void paint(Graphics& g) override
    {
        m_keyboard.paint(g);
    }

    void resized() {
        m_keyboard.setBounds(0, 200, 440, 130);
    }
private:
    MidiKeyboardState state;
    MidiKeyboardComponent m_keyboard;
};
