# Simple Sine Wave Generator
This is a simple sine wave generator project. It can be used as a starting point to learn JUCE libraries and audio signal processing.

Current Issues:
* No mute button
* Sine wave is generated over and over again when buffer is filled (it is not continues, so may produce glitches)
* Time variable is not cleared after period ends (may produce overflows as it is float)
* Time variable adds delta time step after every assigning at **buffer[sample] = value** (sparses sine from true mono to stereo)

## Screenshot of this small application

![screenshot](https://cloud.githubusercontent.com/assets/2100323/17662039/6e05a7ea-62eb-11e6-92a6-8506ad337479.PNG)
