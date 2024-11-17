#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "constants.hpp"
#include "objects.hpp"
#include "textures.hpp"
#include "controllers.hpp"
#include "game_objects.hpp"
#include <memory>

int main() {

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Project Swallow");

    textures::set_textures();

    auto controller = std::make_unique<RombTankInputController>();

    RombTank romb_tank(
        std::move(controller),
        sf::Vector2f(400.0f, 300.0f)
    );

    sf::Clock clock;
    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 300;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        romb_tank.update(time);

        window.clear(sf::Color::White);

        window.draw(romb_tank.get_sprite());

        window.display();
    }

    return 0;
}        
