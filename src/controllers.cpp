#include "controllers.hpp"
#include <iostream>
#include <cmath>

// Common RombTank animation stuff
RombTankController::RombTankController() :
    elapsed_time(0.0), frame_width(32), frame_height(32),
    n_frames(9), frame_duration(0.11), current_frame(0) {};

void RombTankController::updateAnimation(float time, ControlledObject& object) {
    elapsed_time += time;
    if (elapsed_time >= frame_duration) {
        current_frame = (current_frame + 1) % n_frames;
        elapsed_time -= frame_duration;
    }
    updateTextureRectangle(object);
}

void RombTankController::updateTextureRectangle(ControlledObject& object) {
    int column = current_frame % 3;
    int row = current_frame / 3;
    object.set_texture_rectangle(sf::IntRect(column * frame_width, row * frame_height, frame_width, frame_height));
}

// RombTank Random controller
RombTankRandomController::RombTankRandomController() {
    generator = std::mt19937(random_device());
    distribution = std::uniform_real_distribution<>(-1.0, 1.0);
    random_behavior_elapsed_time = 0.0;
    direction = {0.0f, 0.0f};
    moving_flag = false;
}

void RombTankRandomController::update(ControlledObject& object, float time) {
    updateAnimation(time, object);
    random_behavior_elapsed_time += time;
    if (random_behavior_elapsed_time >= 1.0f) {
        moving_flag = !moving_flag;
        if (moving_flag)
            direction = sf::Vector2f(distribution(generator), distribution(generator));
        random_behavior_elapsed_time = 0.0f;
    }

    sf::Vector2f position_updated = object.get_position();

    if (moving_flag)
        position_updated += direction * object.get_speed() * time;

    float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159;
    object.set_sprite_rotation(angle + 90.0);

    object.set_sprite_position(position_updated);
    object.set_position(position_updated);
}

// RombTank Input controller
RombTankInputController::RombTankInputController(sf::RenderWindow& window) :
    RombTankController(), _window(window) {};

void RombTankInputController::updateRotation(ControlledObject& object) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
    sf::Vector2f spritePosition = object.get_sprite().getPosition();
    float dx = mousePosition.x - spritePosition.x;
    float dy = mousePosition.y - spritePosition.y;
    float angle = std::atan2(dy, dx) * 180 / 3.14159;
    object.set_sprite_rotation(angle + 90.0);
}

void RombTankInputController::updatePosition(ControlledObject& object, float time) {
    sf::Vector2f position_updated = object.get_position();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        position_updated.x -= object.get_speed() * time;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        position_updated.x += object.get_speed() * time;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        position_updated.y -= object.get_speed() * time;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        position_updated.y += object.get_speed() * time;
    }

    object.set_sprite_position(position_updated);
    object.set_position(position_updated);
}

void RombTankInputController::update(ControlledObject& object, float time) {
    updateAnimation(time, object);
    updateRotation(object);
    updatePosition(object, time);
}
