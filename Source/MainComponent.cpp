#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "juce_gui_basics\widgets\juce_Slider.h"
#include "juce_gui_basics\widgets\juce_Label.h"

#include <limits>
#include "WhiteNoise.h"
#include "SineWave.h"

#include "OscillatorWave.h"

//==============================================================================
/*
This component lives inside our window, and this is where you should put all
your controls and content.
*/
class MainContentComponent : public AudioAppComponent
{
public:
    //==============================================================================
    MainContentComponent()
    {
        setSize(800, 600);
        setAudioChannels(2, 2);

        addAndMakeVisible(sineWaveOsc);
        addAndMakeVisible(sineWaveOsc2);

        
    }

    ~MainContentComponent()
    {
        shutdownAudio();
    }

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
    {
        // This function will be called when the audio device is started, or when
        // its settings (i.e. sample rate, block size, etc) are changed.
        // You can use this function to initialise any resources you might need,
        // but be careful - it will be called on the audio thread, not the GUI thread.
        // For more details, see the help for AudioProcessor::prepareToPlay()

        m_time = 0.0;
        m_deltaTime = 1 / sampleRate;
    }

    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override
    {
        if (m_time >= std::numeric_limits<float>::max()) {
            m_time = 0.0;
        }

        float *monoBuffer = new float[bufferToFill.numSamples];

        Random random;
        // check if target frequency was changed

        // generate sin wave in mono
        for (int sample = 0; sample < bufferToFill.numSamples; ++sample) {
            float value = sineWaveOsc.nextSample(m_time) + sineWaveOsc2.nextSample(m_time);
            float noise = 0.0; // whiteNoise.nextSample();

            monoBuffer[sample] = value + noise;
            m_time += m_deltaTime;
        }


        // iterate over all available output channels
        for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
        {
            // Get a pointer to the start sample in the buffer for this audio output channel
            float* const buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

            for (int sample = 0; sample < bufferToFill.numSamples; ++sample) {
                buffer[sample] = monoBuffer[sample];
            }
        }
    }

    void releaseResources() override
    {
        // This will be called when the audio device stops, or when it is being
        // restarted due to a setting change.
        // For more details, see the help for AudioProcessor::releaseResources()
    }

    //==============================================================================
    void paint(Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll(Colours::white);
    }

    void resized() override
    {
        sineWaveOsc.setBounds(0, 0, 440, 130);
        sineWaveOsc2.setBounds(0, 130, 440, 130);

    }

private:
    //==============================================================================
    OscillatorWave sineWaveOsc;
    OscillatorWave sineWaveOsc2;

    // Your private member variables go here...
    float m_time;
    float m_deltaTime;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};

// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent() { return new MainContentComponent(); }

#endif  // MAINCOMPONENT_H_INCLUDED
