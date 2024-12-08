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
    _angle_distribution = std::uniform_real_distribution<>(0.0, 2 * 3.14159);
    _random_behavior_elapsed_time = _angle_distribution(_generator) / (4 * 3.14159);
    _next_shot_elapsed_time = 0.0f;
    _time_to_next_shot = _angle_distribution(_generator) / 2.0; // TODO: could be smarter
    _moving_flag = false;
}

void RombTankRandomController::update(ControlledObject& object, float time) {
    RombTank& tank = dynamic_cast<RombTank&>(object); // cast to use tank-specific attributes 

    _random_behavior_elapsed_time += time;
    _next_shot_elapsed_time += time;
    if (_random_behavior_elapsed_time >= 0.5f) {
        _moving_flag = !_moving_flag;
        if (_moving_flag) {
            tank.set_angle(_angle_distribution(_generator));
            tank.set_direction(angle_to_direction(tank.get_angle()));
        }
        _random_behavior_elapsed_time = 0.0f;
    }

    if (tank.get_cooldown_timer() > 0)
        tank.decrement_cooldown_timer(time); 

    if (_next_shot_elapsed_time > _time_to_next_shot) {
        _next_shot_elapsed_time = 0.0f;
        tank.shoot(ControlledObjectsContainer::getInstance());
        _time_to_next_shot = _angle_distribution(_generator) / 2.0;
    }

    sf::Vector2f position_updated = tank.get_position();

    if (_moving_flag)
        position_updated += tank.get_direction() * tank.get_speed() * time;

    updateAnimation(time, tank);
    tank.set_sprite_rotation(tank.get_angle() * 180 / 3.14159 + 90.0);
    tank.set_sprite_position(position_updated);
    tank.set_position(position_updated);
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
