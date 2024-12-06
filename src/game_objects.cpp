#include "game_objects.hpp"
#include <iostream>

RombTank::RombTank(
    std::unique_ptr<Controller> controller,
    sf::Vector2f position
) : ControlledObject(std::move(controller), position) {
    _speed = ROMB_TANK_SPEED;
    _max_health = ROMB_TANK_MAX_HEALTH;
    _health = _max_health;
    _sprite.setTexture(textures::romb_tank_texture);
    _sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    _sprite.setOrigin(16, 16);
    _cooldown = 1.0f;
    _cooldown_timer = 0.0f;
}

float RombTank::get_speed() const {
    return _speed;
}

float RombTank::get_cooldown() const {
    return _cooldown;
}

float RombTank::get_cooldown_timer() const {
    return _cooldown_timer;
}

void RombTank::set_cooldown_timer(float new_time) {
    _cooldown_timer = new_time;
};

void RombTank::decrement_cooldown_timer(float time) {
    _cooldown_timer -= time;
};

void RombTank::shoot(ControlledObjectsContainer& container) {
    if (_cooldown_timer <= 0) {
        auto shell_controller = std::make_unique<ShellController>();
        std::cout << "crreating a shell with angle " << _angle << std::endl;
        container.add_object(
            std::make_unique<Shell>(
                std::move(shell_controller),
                _position,
                _angle,
                200.0f,
                10.0f,
                1.0f
            )
        );
        _cooldown_timer = _cooldown;
    }
}

Shell::Shell(std::unique_ptr<Controller> controller, sf::Vector2f position, float angle, float speed, float damage, float lifetime)
    : ControlledObject(std::move(controller), position)
{
    _speed = speed;
    _damage = damage;
    _lifetime = lifetime;
    _sprite.setTexture(textures::romb_tank_shell_texture);
    set_angle(angle);
}

Shell::~Shell() {
    // explosion
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