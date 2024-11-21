#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

class FPSCounter {

private:

    sf::Clock fpsClock;
    int frameCount = 0;
    float fps = 0.0f;
    sf::Font font;
    sf::Text fpsText;

public:

    FPSCounter();

    void update(sf::RenderWindow& window);
};