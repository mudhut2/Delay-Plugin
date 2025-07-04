//
// Created by hgrov on 6/30/2025.
//

#include "LookAndFeel.h"

RotaryKnobLookAndFeel::RotaryKnobLookAndFeel() {
    setColour(juce::Label::textColourId, Colors::Knob::label);
    setColour(juce::Slider::textBoxTextColourId, Colors::Knob::label);
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

}