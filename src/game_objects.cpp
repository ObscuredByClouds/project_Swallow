#include "game_objects.hpp"

DummyAxis::DummyAxis(
    std::unique_ptr<Controller> controller,
    sf::Vector2f position
) : ControlledObject(std::move(controller), position, 0.0f) {
    _sprite.setTexture(textures::axis_texture);
    _sprite.setPosition(position);
};

RombTank::RombTank(
    std::unique_ptr<Controller> controller,
    sf::Vector2f position,
    float angle
) : ControlledObject(std::move(controller), position, angle) {
    int sprite_pixel_length = 32;
    _speed = ROMB_TANK_SPEED;
    _max_health = ROMB_TANK_MAX_HEALTH;
    _health = _max_health;
    _direction = angle_to_direction(angle);
    _sprite.setTexture(textures::romb_tank_texture);
    _sprite.setTextureRect(sf::IntRect(0, 0, sprite_pixel_length, sprite_pixel_length));
    _sprite.setOrigin(sprite_pixel_length/2, sprite_pixel_length/2);
    _cooldown = 1.0f;
    _cooldown_timer = 0.0f;
    _barrel_displacement_from_sprite_center = {float(sprite_pixel_length/2), 0.0f};
}

RombTank::RombTank(
    std::unique_ptr<Controller> controller,
    sf::Vector2f position
) : RombTank(std::move(controller), position, 0.0f) {}

float RombTank::get_speed() const {
    return _speed;
}

sf::Vector2f RombTank::get_direction() const {
    return _direction;
};

void RombTank::set_direction(sf::Vector2f direction) {
    _direction = direction;
};

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
        float cos_angle = std::cos(_angle);
        float sin_angle = std::sin(_angle);
        sf::Vector2f rotated_offset(
            cos_angle * _barrel_displacement_from_sprite_center.x - sin_angle * _barrel_displacement_from_sprite_center.y,
            sin_angle * _barrel_displacement_from_sprite_center.x + cos_angle * _barrel_displacement_from_sprite_center.y
        );
        container.add_object(
            std::make_unique<Shell>(
                std::move(shell_controller),
                _position + rotated_offset,
                _angle,
                ROMB_TANK_SHELL_SPEED,
                ROMB_TANK_SHELL_DAMAGE,
                ROMB_TANK_SHELL_LIFETIME
            )
        );
        _cooldown_timer = _cooldown;
    }
}

Shell::Shell(std::unique_ptr<Controller> controller, sf::Vector2f position, float angle, float speed, float damage, float lifetime)
    : ControlledObject(std::move(controller), position, angle)
{   
    int sprite_pixel_length = 15;
    _speed = speed;
    _damage = damage;
    _lifetime = lifetime;
    _sprite.setScale(0.7, 0.7);
    _sprite.setRotation(angle * 180 / 3.14159 + 90);
    _sprite.setOrigin(sprite_pixel_length/2.0, sprite_pixel_length/2.0);
    _sprite.setTexture(textures::romb_tank_shell_texture);
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