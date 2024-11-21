#include "include/swallow_lib.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Project Swallow");
    window.setFramerateLimit(999);

    textures::set_textures();

    auto controller = std::make_unique<RombTankInputController>(window);
    RombTank romb_tank(
        std::move(controller),
        sf::Vector2f(400.0f, 300.0f)
    );

    auto random_controller = std::make_unique<RombTankRandomController>();
    RombTank random_romb_tank(
        std::move(random_controller),
        sf::Vector2f(400.0f, 300.0f)
    );

    sf::Clock clock;
    FPSCounter fpsCounter;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        romb_tank.update(time);
        random_romb_tank.update(time);
        window.clear(sf::Color::White);
        window.draw(romb_tank.get_sprite());
        window.draw(random_romb_tank.get_sprite());
        fpsCounter.update(window);
        window.display();
    }

    return 0;
}        
