//
// Created by hgrov on 6/30/2025.
//

#include "LookAndFeel.h"
#include <JuceHeader.h>
#include "BinaryData.h"

const juce::FontOptions Fonts::fontOptions {juce::Typeface::createSystemTypefaceFor(BinaryData::LatoMedium_ttf, BinaryData::LatoMedium_ttfSize)};

juce::Font Fonts::getFont(float height) {
    return juce::Font(Fonts::fontOptions).withHeight(height);
}

juce::Font RotaryKnobLookAndFeel::getLabelFont([[maybe_unused]] juce::Label& label) {
    return Fonts::getFont();
}

RotaryKnobLookAndFeel::RotaryKnobLookAndFeel() {
    setColour(juce::Label::textColourId, Colors::Knob::label);
    setColour(juce::Slider::textBoxTextColourId, Colors::Knob::label);
    setColour(juce::Slider::rotarySliderFillColourId, Colors::Knob::trackActive);

// using slider because createSliderTexbox overwrites the value of Label::outlineColourId with Slider:textboxOutlineColourId
    setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
}

void RotaryKnobLookAndFeel::drawRotarySlider(
    juce::Graphics& g,
    int x, int y, int width, int height,
    float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle,
    juce::Slider& slider )
{
// base (outer) knob rect
    auto bounds = juce::Rectangle<int>(x,y,width,width).toFloat();
    auto knobRect = bounds.reduced(10.0f,10.0f);
// base dropShadow
    auto path = juce::Path();
    path.addEllipse(knobRect);
    dropShadow.drawForPath(g, path);
// draw base knob rect
    g.setColour(Colors::Knob::outline);
    g.fillEllipse(knobRect);
// knob inner gradient
    auto innerRect = knobRect.reduced(2.0f, 2.0f); // auto is juce::Rectangle<float> obj
    auto gradient = juce::ColourGradient(                                    // auto is juce::ColourGradient obj
        Colors::Knob::gradientTop, 0.0f, innerRect.getY(),
        Colors::Knob::gradientBottom, 0.0f, innerRect.getBottom(), false
        );
    g.setGradientFill(gradient);
    g.fillEllipse(knobRect);
// draw arc around outside of knob
    auto center = bounds.getCentre();
    auto radius = bounds.getWidth() / 2.0f;
    auto lineWidth = 3.0f;
    auto arcRadius = radius - lineWidth / 2.0f;

    juce::Path backgroundArc;
    backgroundArc.addCentredArc(center.x, center.y,
                                arcRadius, arcRadius,
                                0.0f, rotaryStartAngle,
                                rotaryEndAngle , true);
    auto strokeType = juce::PathStrokeType(
        lineWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded);
    g.setColour(Colors::Knob::trackBackground);
    g.strokePath(backgroundArc, strokeType);
// draw knob dial to parameter current val based on theta
    auto dialRadius = innerRect.getHeight() / 2.0f - lineWidth;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    juce::Point<float> dialStart(center.x + 10.0f * std::sin(toAngle),
                                center.y - 10.0f * std::cos(toAngle));
    juce::Point<float> dialEnd(center.x + dialRadius * std::sin(toAngle),
                                center.y - dialRadius * std::cos(toAngle));

    juce::Path dialPath;
    dialPath.startNewSubPath(dialStart);
    dialPath.lineTo(dialEnd);
    g.setColour(Colors::Knob::dial);
    g.strokePath(dialPath, strokeType);
// color dial arc (around knob)
    if (slider.isEnabled()) {
        float fromAngle = rotaryStartAngle;
        if (slider.getProperties()["drawFromMiddle"]) {
            fromAngle += (rotaryEndAngle - rotaryStartAngle) / 2.0f;
        }
        juce::Path valueArc;
        valueArc.addCentredArc(center.x, center.y,
                                arcRadius, arcRadius,
                                0.0f, fromAngle,
                                toAngle, true);
        g.setColour(slider.findColour(juce::Slider::rotarySliderFillColourId));
        g.strokePath(valueArc, strokeType);
    }
}

class RotaryKnobLabel : public juce::Label {
public:
    RotaryKnobLabel() : juce::Label() {}

    void mouseWheelMove(const juce::MouseEvent&, const juce::MouseWheelDetails&) override {}

    std::unique_ptr<juce::AccessibilityHandler> createAccessibilityHandler() override {
        return createIgnoredAccessibilityHandler(*this);                                // ????????????????
    }
    juce::TextEditor* createEditorComponent() override
    {
        auto* ed = new juce::TextEditor(getName());
        ed->applyFontToAllText(getLookAndFeel().getLabelFont(*this));
        copyAllExplicitColoursTo(*ed);
        ed->setBorder(juce::BorderSize<int>());
        ed->setIndents(2, 1);
        ed->setJustification(juce::Justification::centredTop);
        ed->setPopupMenuEnabled(false);
        ed->setInputRestrictions(8);
        return ed;
    }
};

juce::Label* RotaryKnobLookAndFeel::createSliderTextBox(juce::Slider& slider) {
    auto l = new RotaryKnobLabel();
    l->setJustificationType(juce::Justification::centred);
    l->setKeyboardType(juce::TextInputTarget::decimalKeyboard);
    l->setColour(juce::Label::textColourId,
    slider.findColour(juce::Slider::textBoxTextColourId));
    l->setColour(juce::TextEditor::textColourId, Colors::Knob::value);
    l->setColour(juce::TextEditor::highlightedTextColourId, Colors::Knob::value);
    l->setColour(juce::TextEditor::highlightColourId,
    slider.findColour(juce::Slider::rotarySliderFillColourId));
    l->setColour(juce::TextEditor::backgroundColourId,
    Colors::Knob::textBoxBackground);
    return l;
}

MainLookAndFeel::MainLookAndFeel() {
    setColour(juce::GroupComponent::textColourId, Colors::Group::label);
    setColour(juce::GroupComponent::outlineColourId, Colors::Group::outline);
}




