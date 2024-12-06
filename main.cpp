#include "include/swallow_lib.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Project Swallow");
    window.setFramerateLimit(999);

    textures::set_textures();

    ControlledObjectsContainer container;

    auto controller = std::make_unique<RombTankInputController>(window);
    container.add_object(std::make_unique<RombTank>(std::move(controller), sf::Vector2f(400.0f, 300.0f)));

    auto random_controller = std::make_unique<RombTankRandomController>();
    container.add_object(std::make_unique<RombTank>(std::move(random_controller), sf::Vector2f(400.0f, 300.0f)));

    auto random_controller_2 = std::make_unique<RombTankRandomController>();
    container.add_object(std::make_unique<RombTank>(std::move(random_controller_2), sf::Vector2f(400.0f, 300.0f)));
    
    auto random_controller_3 = std::make_unique<RombTankRandomController>();
    container.add_object(std::make_unique<RombTank>(std::move(random_controller_3), sf::Vector2f(400.0f, 300.0f)));
    
    auto random_controller_4 = std::make_unique<RombTankRandomController>();
    container.add_object(std::make_unique<RombTank>(std::move(random_controller_4), sf::Vector2f(400.0f, 300.0f)));
    
    auto random_controller_5 = std::make_unique<RombTankRandomController>();
    container.add_object(std::make_unique<RombTank>(std::move(random_controller_5), sf::Vector2f(400.0f, 300.0f)));

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

        container.update(time);

        window.clear(sf::Color::White);
        container.draw(window);
        fpsCounter.update(window);
        window.display();
    }

    return 0;
}        
