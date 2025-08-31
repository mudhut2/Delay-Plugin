#pragma once

#include "PluginProcessor.h"
#include "JuceHeader.h"
#include "Parameters.h"
#include "RotaryKnob.h"
#include "LookAndFeel.h"

//==============================================================================
class AudioPluginAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;

    RotaryKnob gainKnob { "Gain", processorRef.apvts, gainParamID, true };
    RotaryKnob mixKnob { "Mix", processorRef.apvts, mixParamID};
    RotaryKnob delayTimeKnob { "Time", processorRef.apvts, delayTimeParamID};
    RotaryKnob feedbackKnob { "Feedback", processorRef.apvts, feedbackParamID};
    juce::GroupComponent delayGroup, feedbackGroup, outputGroup;

    MainLookAndFeel mainLF;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
