#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "include/constants.hpp"
#include "include/objects.hpp"
#include "include/textures.hpp"

int main() {

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Project Swallow");

    textures::set_textures();

    RombTank romb_tank(
        std::make_unique<TankInputController>(),
        sf::Vector2f(0, 0)
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