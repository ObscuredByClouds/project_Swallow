#include "include/swallow_lib.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Project Swallow");
    window.setFramerateLimit(999);
    textures::set_textures();
/* 
    ControlledObjectsContainer container; // MUST BE REWORKED

    auto controller = std::make_unique<RombTankInputController>(window);
    container.add_object(std::make_unique<RombTank>(std::move(controller), sf::Vector2f(400.0f, 300.0f))); 

    auto random_controller = std::make_unique<RandomRombTankController>();
    container.add_object(std::make_unique<RombTank>(std::move(random_controller), sf::Vector2f(400.0f, 300.0f)));

    auto random_controller_2 = std::make_unique<RandomRombTankController>();
    container.add_object(std::make_unique<RombTank>(std::move(random_controller_2), sf::Vector2f(400.0f, 300.0f)));

    auto random_controller_3 = std::make_unique<RandomRombTankController>();
    container.add_object(std::make_unique<RombTank>(std::move(random_controller_3), sf::Vector2f(400.0f, 300.0f)));

    auto random_controller_4 = std::make_unique<RandomRombTankController>();
    container.add_object(std::make_unique<RombTank>(std::move(random_controller_4), sf::Vector2f(400.0f, 300.0f)));

    auto random_controller_5 = std::make_unique<RandomRombTankController>();
    container.add_object(std::make_unique<RombTank>(std::move(random_controller_5), sf::Vector2f(400.0f, 300.0f)));
*/
    std::vector<RombTank> objects;
    objects.push_back(RombTank(std::move(std::make_unique<InputRombTankController>(window)), sf::Vector2f(300, 400)));
    for(int i = 0; i < 3; i++) {
        objects.push_back(RombTank(std::move(std::make_unique<RandomRombTankController>()), sf::Vector2f(300, 400)));
    }
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
//        container.update(time);
//        container.draw(window);

        for (auto& object : objects) {
            object.update(time);
        }

        for (const auto& object : objects) {
            window.draw(object.get_sprite());
        }

        window.setView(window.getDefaultView());
        fpsCounter.update(window);
        followView(view, objects[0]);
        window.setView(view);
        //std::cout << view.getCenter().x;
        window.display();
    }

    return 0;
}        
