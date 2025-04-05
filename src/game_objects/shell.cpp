#include "game_objects/shell.hpp"

Shell::Shell(
    std::unique_ptr<Controller> controller,
    sf::Vector2f position,
    float angle,
    float speed,
    float damage,
    float lifetime,
    int team
) : DynamicObject(std::move(controller), position, angle) {
    int sprite_pixel_length = 15;
    _speed = speed;
    _damage = damage;
    _lifetime = lifetime;
    _team = team;
    _sprite.setPosition(position);
    _sprite.setScale(0.7, 0.7);
    _sprite.setRotation(angle * 180 / 3.14159 + 90);
    _sprite.setOrigin(sprite_pixel_length/2.0, sprite_pixel_length/2.0);
    _sprite.setTexture(resources::romb_tank_shell_texture);
    _angle = angle;
}

Shell::~Shell() {
    // explode
}

float Shell::get_speed() const {
    return _speed;
}

float Shell::get_damage() const {
    return _damage;
}

float Shell::get_lifetime() const {
    return _lifetime;
}

void Shell::draw(sf::RenderWindow& window) {
    window.draw(this->get_sprite());
}