#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class IWave
{
public:
    IWave() : level(0.0), frequency(0.0), phase(0.0), sampleRate(44100.0) {};
    ~IWave() {};

    void setParams(double plevel, double pfreq, double pphase) {
        this->level = plevel;
        this->frequency = pfreq;
        this->phase = pphase;
    };

    double nextSample(double t, int len) {
        if (this->mute) return 0.0;
        return sample(t, len);
    };

    void setAmplitude(double value) { this->level = value; };
    void setFrequency(double value) { this->frequency = value; };
    void setPhase(double value) { this->phase = value; };

    double getAmplitude() { return this->level; }
    double getFrequency() { return this->frequency; }
    double getPhase() { return phase; }    

    void muteOn() { this->mute = true; }
    void muteOff() { this->mute = false; }
    bool isMuted() { return this->mute; }

    void setSampleRate(int value) { this->sampleRate = value; }
protected:
    double level;
    double frequency;
    double phase;

    double sampleRate;
   
    bool mute = false;

    /**
    * You should override this method
    */
    virtual double sample(double t, int len) = 0;
};

