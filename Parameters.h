//
// Created by hgrov on 6/13/2025.
//

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <JuceHeader.h>

const juce::ParameterID gainParamID { "gain", 1 };
const juce::ParameterID delayTimeParamID { "delay", 1};\
const juce::ParameterID mixParamID { "mix", 1 };

class Parameters {
 public:
    Parameters(juce::AudioProcessorValueTreeState& apvts);

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    void prepareToPlay(double sampleRate) noexcept;
    void reset() noexcept;
    void update() noexcept;
    void smoothen() noexcept;

    float gain = 0.0f;
    float delayTime = 0.0f;
    float mix = 1.0f;

    static constexpr float minDelayTime = 5.0f;
    static constexpr float maxDelayTime = 10000.0f;

private:
    juce::AudioParameterFloat* gainParam;
    juce::LinearSmoothedValue<float> gainSmoother;
    juce::AudioParameterFloat* delayTimeParam;
    float targetDelayTime = 0.0f;
    float coeff = 0.0f; // one-pole smoothing
    juce::AudioParameterFloat* mixParam;
    juce::LinearSmoothedValue<float> mixSmoother;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Parameters)
};

#endif //PARAMETERS_H
