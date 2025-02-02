#include "include/swallow_lib.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Project Swallow");
    window.setFramerateLimit(999);
    textures::set_textures();

    ControlledObjectsContainer& container = ControlledObjectsContainer::getInstance();

    auto zero_controller = std::make_unique<ZeroController>();
    container.add_object(std::make_unique<DummyAxis>(std::move(zero_controller), sf::Vector2f(0.0f, 0.0f)));

    auto controller = std::make_unique<InputRombTankController>(window);
    container.add_object(std::make_unique<RombTank>(std::move(controller), sf::Vector2f(200.0f, 400.0f), 0.0f, 2));

    auto random_controller = std::make_unique<RandomRombTankController>();
    container.add_object(std::make_unique<RombTank>(std::move(random_controller), sf::Vector2f(400.0f, 300.0f), 0.0f, 1));

    auto random_controller_2 = std::make_unique<RandomRombTankController>();
    container.add_object(std::make_unique<RombTank>(std::move(random_controller_2), sf::Vector2f(400.0f, 300.0f), 0.0f, 1));

    auto random_controller_3 = std::make_unique<RandomRombTankController>();
    container.add_object(std::make_unique<RombTank>(std::move(random_controller_3), sf::Vector2f(400.0f, 300.0f), 0.0f, 1));

    auto random_controller_4 = std::make_unique<RandomRombTankController>();
    container.add_object(std::make_unique<RombTank>(std::move(random_controller_4), sf::Vector2f(400.0f, 300.0f), 0.0f, 1));

    auto random_controller_5 = std::make_unique<RandomRombTankController>();
    container.add_object(std::make_unique<RombTank>(std::move(random_controller_5), sf::Vector2f(400.0f, 300.0f), 0.0f, 1));


    sf::Clock clock;
    FPSCounter fpsCounter;
    sf::View view = window.getDefaultView();

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        container.update(time);
        container.draw(window);

        window.setView(window.getDefaultView());
        fpsCounter.update(window);
        view_follow_target(view, container[1]);
        window.setView(view);
        window.display();
    }

    return 0;
}        
