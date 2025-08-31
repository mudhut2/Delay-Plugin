#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    delayGroup.setText("Delay");
    delayGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
    delayGroup.addAndMakeVisible(delayTimeKnob);
    addAndMakeVisible(delayGroup);

    feedbackGroup.setText("Feedback");
    feedbackGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
    addAndMakeVisible(feedbackGroup);
    feedbackGroup.addAndMakeVisible(feedbackKnob);

    outputGroup.setText("Output");
    outputGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
    outputGroup.addAndMakeVisible(mixKnob);
    outputGroup.addAndMakeVisible(gainKnob);
    addAndMakeVisible(outputGroup);

    gainKnob.slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::green);

    setLookAndFeel(&mainLF);

    setSize (500, 330);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    auto noise = juce::ImageCache::getFromMemory(BinaryData::synthTex_png, BinaryData::synthTex_pngSize);
    auto fillType = juce::FillType(noise, juce::AffineTransform::scale(0.5f));
    g.setFillType(fillType);
    g.fillRect(getLocalBounds());


    auto rect = getLocalBounds().withHeight(40);
    g.setColour(Colors::header);
    g.fillRect(rect);

    auto image = juce::ImageCache::getFromMemory(BinaryData::Logo_png, BinaryData::Logo_pngSize);

    int destWidth = image.getWidth() / 2;
    int destHeight = image.getHeight() / 2;

    g.drawImage(image, getWidth() / 2 - destWidth / 2, 0, destWidth, destHeight,
                0, 0, image.getWidth(), image.getHeight());
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    int y = 50;
    int height = bounds.getHeight() - 60;
// position groups
    delayGroup.setBounds(10, y, 110, height);
    outputGroup.setBounds(bounds.getWidth() - 160, y , 150, height);
    feedbackGroup.setBounds(delayGroup.getRight() + 10, y, outputGroup.getX() - delayGroup.getRight() - 20, height);
// position knobs inside groups
    delayTimeKnob.setTopLeftPosition(20, 20);
    mixKnob.setTopLeftPosition(20, 20);
    gainKnob.setTopLeftPosition(mixKnob.getX(), mixKnob.getBottom() + 10);
    feedbackKnob.setTopLeftPosition(20,20);
}
