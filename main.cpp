#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "constants.hpp"
#include "objects.hpp"
#include "textures.hpp"
#include "controllers.hpp"
#include "game_objects.hpp"
#include <memory>
#include <iostream>

int main() {

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Project Swallow");
    window.setFramerateLimit(180);

    textures::set_textures();

    auto controller = std::make_unique<RombTankInputController>(window);

    RombTank romb_tank(
        std::move(controller),
        sf::Vector2f(400.0f, 300.0f)
    );

    sf::Clock clock;

    sf::Clock fpsClock;
    int frameCount = 0;
    float fps = 0.0f;
    sf::Font font;
    if (!font.loadFromFile("./fonts/arial.ttf")) {
        std::cerr << "Ошибка загрузки шрифта" << std::endl;
        return -1;
    }
    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(24); // Размер текста
    fpsText.setFillColor(sf::Color::Black); // Цвет текста
    fpsText.setPosition(0.f, 0.f); // Позиция текста

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        frameCount++;
        if (fpsClock.getElapsedTime().asSeconds() >= 1.0f) {
            fps = frameCount / fpsClock.restart().asSeconds();
            frameCount = 0;

            // Обновление текста FPS
            fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
        }

        romb_tank.update(time);
        window.clear(sf::Color::White);
        window.draw(romb_tank.get_sprite());
        window.draw(fpsText);
        window.display();
    }

    return 0;
}        
