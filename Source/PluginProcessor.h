#pragma once 

#include <juce_audio_processors/juce_audio_processors.h>
#include <atomic> 
#include "TestTone.h"
#include "OnePoleFilter.h"

class SimpleDistortionAudioProcessor : public juce::AudioProcessor
{
public:
    SimpleDistortionAudioProcessor();
    ~SimpleDistortionAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    std::atomic<float> drive { 1.0f };
    std::atomic<float> tone { 8000.0f };
    std::atomic<float> mix { 1.0f };
    std::atomic<bool> testToneOn { false };

    private:
        TestTone testTone;
        OnePoleFilter filters[2];
        double currentSampleRate = 44100.0;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDistortionAudioProcessor)
};