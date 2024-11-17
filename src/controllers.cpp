#include "controllers.hpp"
#include <iostream>
#include <cmath>

RombTankInputController::RombTankInputController(sf::RenderWindow& window) : _window(window), elapsed_time(0.0),
    frame_width(32), frame_height(32), n_frames(9), frame_duration(0.11), current_frame(0) {};
    
void RombTankInputController::update(ControlledObject& object, float time) {
    auto* tank = dynamic_cast<RombTank*>(&object);
    if (!tank) return;
    sf::Vector2f position_updated = tank->get_position();

    elapsed_time += time;
    if (elapsed_time >= frame_duration) {
        current_frame = (current_frame + 1) % n_frames;

        int column = current_frame % 3;
        int row = current_frame / 3;   

        object.set_texture_rectangle(sf::IntRect(column * frame_width, row * frame_height, frame_width, frame_height));

        elapsed_time -= frame_duration;
    }

    sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
    sf::Vector2f spritePosition = object.get_sprite().getPosition();
    float dx = mousePosition.x - spritePosition.x;
    float dy = mousePosition.y - spritePosition.y;
    float angle = std::atan2(dy, dx) * 180 / 3.14159;
    object.set_sprite_rotation(angle + 90.0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        position_updated.x -= tank->get_speed() * time;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        position_updated.x += tank->get_speed() * time;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        position_updated.y -= tank->get_speed() * time;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        position_updated.y += tank->get_speed() * time;
    }

    object.set_sprite_position(position_updated);
    object.set_position(position_updated);
}