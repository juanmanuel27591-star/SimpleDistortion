#include "PluginProcessor.h"
#include "PluginEditor.h"

SimpleDistortionAudioProcessor::SimpleDistortionAudioProcessor()
    : AudioProcessor (BusesProperties()
    .withInput ("Input", juce::AudioChannelSet::stereo(), true)
    .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
}

SimpleDistortionAudioProcessor:: ~SimpleDistortionAudioProcessor()
{
}

const juce::String SimpleDistortionAudioProcessor::getName() const
{    
    return JucePlugin_Name;
}

bool SimpleDistortionAudioProcessor::acceptsMidi() const
{
    return false;
}

bool SimpleDistortionAudioProcessor::producesMidi() const 
{
    return false;
}

bool SimpleDistortionAudioProcessor::isMidiEffect() const
{
    return false;
}

double SimpleDistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleDistortionAudioProcessor::getNumPrograms()
{
    return 1;
}

int SimpleDistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleDistortionAudioProcessor::setCurrentProgram (int)
{
}

const juce::String SimpleDistortionAudioProcessor::getProgramName (int)
{
    return {};
}

void SimpleDistortionAudioProcessor::changeProgramName (int, const juce::String&)
{
}

void SimpleDistortionAudioProcessor::prepareToPlay (double sampleRate, int)
{
    testTone.prepare (sampleRate);
    currentSampleRate = sampleRate;

    for (auto& filter : filters)
        filter.reset();
}

void SimpleDistortionAudioProcessor::releaseResources()
{
}

bool SimpleDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const auto& out = layouts.getMainOutputChannelSet();
    const auto& in = layouts.getMainInputChannelSet();

    if (out != juce::AudioChannelSet::mono()
    && out != juce::AudioChannelSet::stereo())
    return false;

    return out == in;
}

void SimpleDistortionAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    for (int ch = getTotalNumInputChannels(); ch < getTotalNumOutputChannels(); ++ch)
    buffer.clear (ch, 0, buffer.getNumSamples());
    
    const bool toneOn = testToneOn.load();
    const float driveValue = drive.load();
    const float mixValue = mix.load();
    const float toneValue = tone.load();
    const float coefficient = 1.0f - std::exp (-juce::MathConstants<float>::twoPi * toneValue / (float) currentSampleRate);
    const int numChannels = getTotalNumInputChannels();

    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        const float testSample = toneOn ? testTone.getNextSample() : 0.0f;

        for (int ch = 0; ch < numChannels; ++ch)
        {
            const float x = buffer.getSample (ch, i) + testSample;
            const float shaped = std::tanh (x * driveValue);
            const float filtered = filters[ch].process (shaped,coefficient);
            const float out = x * (1.0f - mixValue) + filtered * mixValue;
            buffer.setSample (ch, i, out);
        }
    }
}

bool SimpleDistortionAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* SimpleDistortionAudioProcessor::createEditor()
{
    return new SimpleDistortionAudioProcessorEditor (*this);
}

void SimpleDistortionAudioProcessor::getStateInformation (juce::MemoryBlock&)
{
}

void SimpleDistortionAudioProcessor::setStateInformation (const void*, int)
{
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleDistortionAudioProcessor();
}