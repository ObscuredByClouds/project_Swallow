#include "shell_c.hpp"

ShellController::ShellController() {
    _elapsed_time = 0.0f;
}

void ShellController::update(DynamicObject& object, float time) {
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
