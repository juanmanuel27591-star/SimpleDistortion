#include "PluginEditor.h"

SimpleDistortionAudioProcessorEditor::SimpleDistortionAudioProcessorEditor (SimpleDistortionAudioProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p)
{
    driveSlider.setSliderStyle (juce::Slider::LinearHorizontal);
    driveSlider.setTextBoxStyle (juce::Slider::TextBoxRight, false, 70, 20);
    driveSlider.setRange (1.0, 20.0, 0.01);
    driveSlider.setValue (audioProcessor.drive.load(), juce::dontSendNotification);
    driveSlider.onValueChange = [this]
    {
        audioProcessor.drive = (float) driveSlider.getValue();
    };
    addAndMakeVisible (driveSlider);
    driveLabel.setText ("Drive", juce::dontSendNotification);
    driveLabel.attachToComponent (&driveSlider, true);
    addAndMakeVisible (driveLabel);

    toneSlider.setSliderStyle (juce::Slider::LinearHorizontal);
    toneSlider.setTextBoxStyle (juce::Slider::TextBoxRight, false, 70, 20);
    toneSlider.setRange (500.0, 16000.0, 1.0);
    toneSlider.setValue (audioProcessor.tone.load(), juce::dontSendNotification);
    toneSlider.onValueChange = [this]
    {
        audioProcessor.tone = (float) toneSlider.getValue();
    };
    addAndMakeVisible (toneSlider);
    toneLabel.setText ("Tone", juce::dontSendNotification);
    toneLabel.attachToComponent (&toneSlider, true);
    addAndMakeVisible (toneLabel);

    mixSlider.setSliderStyle (juce::Slider::LinearHorizontal);
    mixSlider.setTextBoxStyle (juce::Slider::TextBoxRight, false, 70, 20);
    mixSlider.setRange (0.0, 1.0, 0.01);
    mixSlider.setValue (audioProcessor.mix.load(), juce::dontSendNotification);
    mixSlider.onValueChange = [this]
{
    audioProcessor.mix = (float) mixSlider.getValue();
};
addAndMakeVisible (mixSlider);
mixLabel.setText ("Mix", juce::dontSendNotification);
mixLabel.attachToComponent (&mixSlider, true);
addAndMakeVisible (mixLabel);

testToneButton.setButtonText (audioProcessor.testToneOn.load() ? "Stop" : "Play");
testToneButton.onClick = [this]
{
    const bool nowOn = ! audioProcessor.testToneOn.load();
    audioProcessor.testToneOn = nowOn;
    testToneButton.setButtonText (nowOn ? "Stop" : "Play");
};
addAndMakeVisible (testToneButton);

setSize (400, 220);
}

SimpleDistortionAudioProcessorEditor:: ~SimpleDistortionAudioProcessorEditor()
{
}

void SimpleDistortionAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void SimpleDistortionAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced (20);
    testToneButton.setBounds (area.removeFromBottom (30));
    area.removeFromLeft (60);
    auto rowHeight = area.getHeight() / 3;

    driveSlider.setBounds (area.removeFromTop (rowHeight));
    toneSlider.setBounds (area.removeFromTop (rowHeight));
    mixSlider.setBounds (area);
}