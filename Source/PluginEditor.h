#pragma once

#include "PluginProcessor.h"

class SimpleDistortionAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit SimpleDistortionAudioProcessorEditor (SimpleDistortionAudioProcessor&);
    ~SimpleDistortionAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SimpleDistortionAudioProcessor& audioProcessor;

    juce::Slider driveSlider;
    juce::Slider toneSlider;
    juce::Slider mixSlider;

    juce::Label driveLabel;
    juce::Label toneLabel;
    juce::Label mixLabel;

    juce::TextButton testToneButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDistortionAudioProcessorEditor)
};