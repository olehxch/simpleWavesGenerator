#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include <limits>
#include "WhiteNoise.h"
#include "SineWave.h"
#include "SquareWave.h"
#include "SawtoothWave.h"
#include "TriangleWave.h"

#include "OscillatorWave.h"
#include "WaveformViewComponent.h"
#include "SpectralViewComponent.h"

//==============================================================================
/*
This component lives inside our window, and this is where you should put all
your controls and content.
*/
class MainContentComponent :    public AudioAppComponent
{
public:
    //==============================================================================
    MainContentComponent()
    {
        setSize(800, 600);
        setAudioChannels(2, 2);

        sineWaveOsc.setWaveType(new SineWave());
        squareWaveOsc.setWaveType(new SquareWave());
        sawWaveOsc.setWaveType(new SawtoothWave());
        triangleWaveOsc.setWaveType(new TriangleWave());

        sineWaveOsc.setTitle("Sine wave");
        squareWaveOsc.setTitle("Square wave");
        sawWaveOsc.setTitle("Saw wave");
        triangleWaveOsc.setTitle("Triangle wave");
        
        sineWaveOsc.muteOn();
        squareWaveOsc.muteOn();
        sawWaveOsc.muteOn();
        triangleWaveOsc.muteOn();

        sineWaveOsc.setColor(Colour::fromRGB(0x4E, 0x99, 0xFE) );
        squareWaveOsc.setColor(Colour::fromRGB(0xCC, 0x3B, 0xFA) );
        sawWaveOsc.setColor(Colour::fromRGB(0xFC, 0xFE, 0x31) );
        triangleWaveOsc.setColor(Colour::fromRGB(0x37, 0xDD, 0x77) );

        addAndMakeVisible(waveformView);
        addAndMakeVisible(spectralView);

        addAndMakeVisible(sineWaveOsc);
        addAndMakeVisible(squareWaveOsc);
        addAndMakeVisible(sawWaveOsc);
        addAndMakeVisible(triangleWaveOsc);

        m_isInitialized = true;
    }

    ~MainContentComponent()
    {
        shutdownAudio();
    }

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
    {
        m_time = 0.0;
        m_deltaTime = 1.0 / sampleRate;
        monoBuffer = new float[samplesPerBlockExpected] {0};
    }

    void mixWaves(float* pmonoBuffer, int numSamples) {
        Random random;

        // generate sin wave in mono
        for (int sample = 0; sample < numSamples; ++sample) {
            double sine = sineWaveOsc.nextSample(m_time, numSamples);
            double square = squareWaveOsc.nextSample(m_time, numSamples);
            double saw = sawWaveOsc.nextSample(m_time, numSamples);
            double triangle = triangleWaveOsc.nextSample(m_time, numSamples);

            pmonoBuffer[sample] = sine + square + saw + triangle;
            m_time += m_deltaTime;
        }
    }

    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override
    {
        if (m_time >= std::numeric_limits<float>::max()) {
            m_time = 0.0;
        }

        std::fill(monoBuffer, monoBuffer + bufferToFill.numSamples, 0);
        mixWaves(monoBuffer, bufferToFill.numSamples);

        // iterate over all available output channels
        for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
        {
            // Get a pointer to the start sample in the buffer for this audio output channel
            float* const buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

            for (int sample = 0; sample < bufferToFill.numSamples; ++sample) {
                buffer[sample] = monoBuffer[sample];
            }
        }

        // update waveform and spectral views
        waveformView.fillBuffer(monoBuffer, bufferToFill.numSamples);
        spectralView.fillBuffer(monoBuffer, bufferToFill.numSamples);    
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
        waveformView.repaint();
        spectralView.repaint();
    }

    void resized() override
    {
        Rectangle<int> area(getLocalBounds());
        
        sineWaveOsc.setBounds(0, 0, sineWaveOsc.getBounds().getWidth(), sineWaveOsc.getBounds().getHeight());
        squareWaveOsc.setBounds(0, 150, squareWaveOsc.getBounds().getWidth(), sineWaveOsc.getBounds().getHeight());
        sawWaveOsc.setBounds(0, 300, sawWaveOsc.getBounds().getWidth(), sineWaveOsc.getBounds().getHeight());
        triangleWaveOsc.setBounds(0, 450, triangleWaveOsc.getBounds().getWidth(), sineWaveOsc.getBounds().getHeight());

        // waveform view
        waveformView.setBounds(440, 0, waveformView.getBounds().getWidth(), waveformView.getBounds().getHeight());
        spectralView.setBounds(440, 300, spectralView.getBounds().getWidth(), spectralView.getBounds().getHeight());
    }
    
private:
    //==============================================================================
    // oscillators
    OscillatorWave sineWaveOsc;
    OscillatorWave squareWaveOsc;
    OscillatorWave sawWaveOsc;
    OscillatorWave triangleWaveOsc;

    WaveformViewComponent waveformView;
    SpectralViewComponent spectralView;

    // Your private member variables go here...
    double m_time;
    double m_deltaTime;
    float *monoBuffer;

    bool m_isInitialized = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};

// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent() { return new MainContentComponent(); }

#endif  // MAINCOMPONENT_H_INCLUDED
