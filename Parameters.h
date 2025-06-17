//
// Created by hgrov on 6/13/2025.
//

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <JuceHeader.h>

const juce::ParameterID gainParamID { "gain", 1 };

class Parameters {
public:
    Parameters(juce::AudioProcessorValueTreeState& apvts);

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    void prepareToPlay(double sampleRate) noexcept;
    void reset() noexcept;
    void update() noexcept;
    void smoothen() noexcept;

    float gain = 0.0f;

    static constexpr float miniDelayTime = 5.0f;
    static constexpr float maxDelayTime = 5000.0f;

private:
    juce::AudioParameterFloat* gainParam;
    juce::LinearSmoothedValue<float> gainSmoother;
};

#endif //PARAMETERS_H
