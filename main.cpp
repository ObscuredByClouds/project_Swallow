#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "include/constants.hpp"
#include "include/objects.hpp"
#include "include/textures.hpp"
#include "include/player_controller.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Project Swallow");

    textures::set_textures();

    Player* player = new Player(textures::player_texture, sf::Vector2f(0, 0), 100);

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

        player->update(time);

        window.clear(sf::Color::White);

        window.draw(player->get_sprite());

        window.display();
    }

    return 0;
   }