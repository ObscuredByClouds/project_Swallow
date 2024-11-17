#include "game_objects.hpp"

RombTank::RombTank(
    std::unique_ptr<Controller> controller,
    sf::Vector2f position
) : ControlledObject(std::move(controller), position) {
    speed = ROMB_TANK_SPEED;
    max_health = ROMB_TANK_MAX_HEALTH;
    health = max_health;
    _sprite.setTexture(textures::romb_tank_texture);
    _sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    _sprite.setOrigin(16, 16);
}

float RombTank::get_speed() {
    return speed;
}
