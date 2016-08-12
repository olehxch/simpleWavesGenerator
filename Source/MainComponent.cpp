#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "juce_gui_basics\widgets\juce_Slider.h"
#include "juce_gui_basics\widgets\juce_Label.h"

//==============================================================================
/*
This component lives inside our window, and this is where you should put all
your controls and content.
*/
class MainContentComponent : public AudioAppComponent, public Slider::Listener
{
public:
    //==============================================================================
    MainContentComponent()
    {
        setSize(480, 120);

        // specify the number of input and output channels that we want to open
        setAudioChannels(2, 2);

        // volume slider
        addAndMakeVisible(volumeSlider);
        volumeSlider.setRange(0.0, 1.0);
        volumeSlider.setTextValueSuffix("");
        volumeSlider.setValue(0.25);
        volumeSlider.addListener(this);
        //volumeSlider.setSkewFactorFromMidPoint(0.5);

        volumeLabel.setText("Volume", dontSendNotification);
        volumeLabel.attachToComponent(&volumeSlider, true);

        // phase slider
        addAndMakeVisible(phaseSlider);
        phaseSlider.setRange(0.0, 1.0);
        phaseSlider.setTextValueSuffix(" ~");
        phaseSlider.setValue(0.0);
        phaseSlider.addListener(this);

        phaseLabel.setText("Phase", dontSendNotification);
        phaseLabel.attachToComponent(&phaseSlider, true);

        // freq slider
        addAndMakeVisible(freqSlider);
        freqSlider.setRange(10, 22000);
        freqSlider.setTextValueSuffix(" Hz");
        freqSlider.setValue(500.0);
        freqSlider.addListener(this);
        freqSlider.setSkewFactorFromMidPoint(500);

        freqLabel.setText("Freq", dontSendNotification);
        freqLabel.attachToComponent(&freqSlider, true);
    }

    ~MainContentComponent()
    {
        shutdownAudio();
    }

    void sliderValueChanged(Slider *slider) {
        m_amplitude = (float)volumeSlider.getValue();
        m_frequency = (float)freqSlider.getValue();
        m_phase = (float)phaseSlider.getValue();
    }

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
    {
        // This function will be called when the audio device is started, or when
        // its settings (i.e. sample rate, block size, etc) are changed.
        // You can use this function to initialise any resources you might need,
        // but be careful - it will be called on the audio thread, not the GUI thread.
        // For more details, see the help for AudioProcessor::prepareToPlay()

        m_amplitude = 0.5;
        m_frequency = 500;
        m_phase = 0.0;
        m_time = 0.0;
        m_deltaTime = 1 / sampleRate;
    }

    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override
    {
        // Your audio-processing code goes here!
        // For more details, see the help for AudioProcessor::getNextAudioBlock()
        // Right now we are not producing any data, in which case we need to clear the buffer
        // (to prevent the output of random noise)
        //bufferToFill.clearActiveBufferRegion();

        // iterate over all available output channels
        m_time = 0;
        for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
        {
            // Get a pointer to the start sample in the buffer for this audio output channel
            float* const buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

            for (int sample = 0; sample < bufferToFill.numSamples; ++sample) {
                float f = m_frequency;
                float value = m_amplitude * sin(2 * double_Pi*f*m_time + m_phase);

                buffer[sample] = value;
                m_time += m_deltaTime;
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
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
        const int sliderLeft = 50;
        volumeSlider.setBounds(sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
        phaseSlider.setBounds(sliderLeft, 50, getWidth() - sliderLeft - 10, 20);
        freqSlider.setBounds(sliderLeft, 80, getWidth() - sliderLeft - 10, 20);
    }

private:
    //==============================================================================

    // Your private member variables go here...
    float m_amplitude;
    float m_frequency;
    float m_phase;
    float m_time;
    float m_deltaTime;

    // GUI
    Slider volumeSlider;
    Slider freqSlider;
    Slider phaseSlider;
    Label volumeLabel;
    Label freqLabel;
    Label phaseLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};

// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent() { return new MainContentComponent(); }

#endif  // MAINCOMPONENT_H_INCLUDED
