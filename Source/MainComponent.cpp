#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() {
    _nextIteration.setButtonText("Next iteration");
    _nextIteration.addListener(this);
    _skipIteration.setText("1");
    addAndMakeVisible(_nextIteration);
    addAndMakeVisible(_skipIteration);

    setSize (800, 800);
    _imageAutomaton = juce::Image(juce::Image::PixelFormat::RGB, getWidth() / 2, getWidth() / 2, false);

    fillImage();
}

MainComponent::~MainComponent()
{
    _nextIteration.removeListener(this);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    //...
    g.setColour(getLookAndFeel().findColour(juce::Slider::thumbColourId));
    
    g.drawImage(_imageAutomaton, getWidth() / 2 - _imageAutomaton.getWidth() / 2, getHeight() / 2 - _imageAutomaton.getHeight() / 2, _imageAutomaton.getWidth(), _imageAutomaton.getHeight(), 0, 0, _imageAutomaton.getWidth(), _imageAutomaton.getHeight());
}

void MainComponent::resized() {    
    _nextIteration.setBounds(0, 0, 100, 60);
    _skipIteration.setBounds(_nextIteration.getWidth() + 10, 0, 100, 60);
}

void MainComponent::fillImage() {
    juce::Random randomGenerator{};
    for (std::size_t i = 0; i < _imageAutomaton.getWidth(); i++) {
        for (std::size_t j = 0; j < _imageAutomaton.getHeight(); j++) {
            auto value = randomGenerator.nextBool();
            
            _imageAutomaton.setPixelAt(i, j, boolToColor(value));
        }
    }
}

void MainComponent::updateImage() {
    juce::Image newImage = _imageAutomaton;
    for (std::size_t i = 0; i < _imageAutomaton.getWidth(); i++) {
        for (std::size_t j = 0; j < _imageAutomaton.getHeight(); j++) {
            auto colorOfPixer = _imageAutomaton.getPixelAt(i, j);
            auto inverseColor = boolToColor(!colorToBool(colorOfPixer));
            auto countOfAnyColor = numberColorInRangePixel(_imageAutomaton, i, j, inverseColor);

            static constexpr std::array<std::size_t, 4> equalNumber {3, 6, 7, 8};

            for (const auto& number : equalNumber) {
                if (number == countOfAnyColor) {
                    newImage.setPixelAt(i, j, inverseColor);
                    break;
                }
            }            
        }
    }

    _imageAutomaton = newImage;
    repaint();
}

void MainComponent::buttonClicked(juce::Button* button) {
    if (button == &_nextIteration) {
        auto value = _skipIteration.getText();
        try {
            int skipIteration = std::stoi(value.toStdString());
            for (int i = 0; i < skipIteration; i++) {
                updateImage();
            }
        }
        catch(...) {

        }
        
        
    }   
}

bool MainComponent::colorToBool(juce::Colour value) {
    return value == juce::Colours::blue;
}

juce::Colour MainComponent::boolToColor(bool value) {
    return value ? juce::Colours::blue : juce::Colours::green;
}

std::size_t MainComponent::numberColorInRangePixel(juce::Image& targetImage, int x, int y, juce::Colour color) {
    std::size_t result = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            int targetX = x + i;
            int targetY = y + j;
            if (!(targetX == x && targetY == y) && (targetX <= targetImage.getWidth() && targetX >= 0) && (targetY <= targetImage.getHeight() && (targetY >= 0))) {
                if (targetImage.getPixelAt(targetX, targetY) == color) {
                    ++result;
                }
            }
        }
    }

    return result;
}