//
// Created by hgrov on 6/27/2025.
//

#ifndef ROTARYKNOB_H
#define ROTARYKNOB_H
#include <JuceHeader.h>


class RotaryKnob : public juce::Component{
public:
        RotaryKnob(const juce::String& text, juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& parameterID);
        ~RotaryKnob() override;

        //void paint (juce::Graphics&) override;
        void resized() override;

        juce::Slider slider;
        juce::Label label;
        juce::AudioProcessorValueTreeState::SliderAttachment attachment;
private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RotaryKnob)
};

#endif //ROTARYKNOB_H
