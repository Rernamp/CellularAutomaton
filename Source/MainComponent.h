#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component, public juce::Button::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;

private:
    void fillImage();
    void updateImage();
    std::size_t numberColorInRangePixel(juce::Image& targetImage, int x, int y, juce::Colour color);
    juce::Image _imageAutomaton {};
    juce::TextEditor _skipIteration;

    bool colorToBool(juce::Colour value);
    juce::Colour boolToColor(bool value);

    juce::TextButton _nextIteration;
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
