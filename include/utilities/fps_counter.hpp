#pragma once

#include <SFML/Graphics.hpp>
#include "resources.hpp"

class FPSCounter {

private:

    sf::Clock fpsClock;
    int frameCount = 0;
    float fps = 0.0f;
    sf::Text fpsText;

public:

    FPSCounter();

    void update(sf::RenderWindow& window);
};