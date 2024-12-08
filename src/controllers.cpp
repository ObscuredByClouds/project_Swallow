#include "controllers.hpp"
#include <cmath>

void ZeroController::update(ControlledObject& /*object*/, float /*time*/) {}

// Common RombTank animation stuff
RombTankController::RombTankController() :
    _elapsed_time(0.0), _frame_width(32), _frame_height(32),
    _n_frames(9), _frame_duration(0.11), _current_frame(0) {};

void RombTankController::updateAnimation(float time, ControlledObject& object) {
    _elapsed_time += time;
    if (_elapsed_time >= _frame_duration) {
        _current_frame = (_current_frame + 1) % _n_frames;
        _elapsed_time -= _frame_duration;
    }
    updateTextureRectangle(object);
}

void RombTankController::updateTextureRectangle(ControlledObject& object) {
    int column = _current_frame % 3;
    int row = _current_frame / 3;
    object.set_texture_rectangle(sf::IntRect(column * _frame_width, row * _frame_height, _frame_width, _frame_height));
}

// RombTank Random controller
RombTankRandomController::RombTankRandomController() {
    _generator = std::mt19937(_random_device());
    _distribution = std::uniform_real_distribution<>(-1.0, 1.0);
    _random_behavior_elapsed_time = _distribution(_generator);
    _direction = {0.0f, 0.0f};
    _moving_flag = false;
}

void RombTankRandomController::update(ControlledObject& object, float time) {
    updateAnimation(time, object);
    _random_behavior_elapsed_time += time;
    if (_random_behavior_elapsed_time >= 1.0f) {
        _moving_flag = !_moving_flag;
        if (_moving_flag)
            _direction = sf::Vector2f(_distribution(_generator), _distribution(_generator));
        _random_behavior_elapsed_time = 0.0f;
    }

    RombTank& tank = dynamic_cast<RombTank&>(object); // can be separated
    if (tank.get_cooldown_timer() > 0)
        tank.decrement_cooldown_timer(time); 

    if (_random_behavior_elapsed_time > 0.5 && _random_behavior_elapsed_time < 0.55 && _distribution(_generator) < -0.9) {
        tank.shoot(ControlledObjectsContainer::getInstance()); // Pass the container to the shoot method
    } // naive approach

    sf::Vector2f position_updated = object.get_position();

    if (_moving_flag)
        position_updated += _direction * object.get_speed() * time;

    float angle = std::atan2(_direction.y, _direction.x);

    object.set_sprite_rotation(angle * 180 / 3.14159 + 90.0);
    object.set_angle(angle);
    object.set_sprite_position(position_updated);
    object.set_position(position_updated);
}

// RombTank Input controller
RombTankInputController::RombTankInputController(sf::RenderWindow& window) :
    RombTankController(), _window(window) {};

void RombTankInputController::updateRotation(ControlledObject& object, float time) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
    sf::Vector2f spritePosition = object.get_sprite().getPosition();
    float dx = mousePosition.x - spritePosition.x;
    float dy = mousePosition.y - spritePosition.y;
    float angle = std::atan2(dy, dx);

    RombTank& tank = dynamic_cast<RombTank&>(object);
    if (tank.get_cooldown_timer() > 0)
        tank.decrement_cooldown_timer(time); // time is rquired only here. Might be better to separate shot processing

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        tank.shoot(ControlledObjectsContainer::getInstance()); // Pass the container to the shoot method
    }
    object.set_angle(angle);
    object.set_sprite_rotation(angle * 180 / 3.14159 + 90.0);
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
    updateRotation(object, time);
    updatePosition(object, time);
}


ShellController::ShellController() {
    _elapsed_time = 0.0f;
}

void ShellController::update(ControlledObject& object, float time) {
    Shell* shell = dynamic_cast<Shell*>(&object);
    if (time + _elapsed_time > shell->get_lifetime())
        object.set_terminate();
    else
        _elapsed_time += time;
    sf::Vector2f direction = sf::Vector2f(std::cos(object.get_angle()), std::sin(object.get_angle()));
    sf::Vector2f position_updated = object.get_position();
    position_updated += direction * object.get_speed() * time;

    object.set_sprite_position(position_updated);
    object.set_position(position_updated);
}
