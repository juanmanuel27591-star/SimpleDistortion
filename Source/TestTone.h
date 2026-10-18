#pragma once

#include <juce_core/juce_core.h>
#include <cmath>

class TestTone
{
public:
    void prepare (double newSampleRate)
    {
        sampleRate = newSampleRate;
        phase = 0.0;
    }

    float getNextSample()
    {
        const float sample = amplitude * (float) std::sin (phase);

        phase += juce::MathConstants<double>::twoPi * frequency / sampleRate;

        if (phase >= juce::MathConstants<double>::twoPi)
        phase -= juce::MathConstants<double>::twoPi;

        return sample;
    }

private:
    double sampleRate = 44100.0;
    double phase = 0.0;
    double frequency = 220.0;
    float amplitude = 0.25f;
};