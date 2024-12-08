#include "utilities/fps_counter.hpp"
#include <filesystem>

FPSCounter::FPSCounter() {
    std::filesystem::path relativePathToFont = "./fonts/arial.ttf";
    if (!font.loadFromFile(relativePathToFont.native())) {
        std::cerr << "Error: font is not loaded" << std::endl;
        return;
    }
    fpsText.setFont(font);
    fpsText.setCharacterSize(24); // Text size
    fpsText.setFillColor(sf::Color::Black); // Text color
    fpsText.setPosition(0.f, 0.f); // Text position
}

void FPSCounter::update(sf::RenderWindow& window) {
    frameCount++;
    if (fpsClock.getElapsedTime().asSeconds() >= 1.0f) {
        fps = frameCount / fpsClock.restart().asSeconds();
        frameCount = 0;

        // Update FPS text
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
    }
    window.draw(fpsText);
}