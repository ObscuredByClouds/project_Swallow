#include "game_objects.hpp"

DummyAxis::DummyAxis(
    std::unique_ptr<Controller> controller,
    sf::Vector2f position
) : DynamicObject(std::move(controller), position, 0.0f) {
    _sprite.setTexture(textures::axis_texture);
    _sprite.setPosition(position);
};

void DummyAxis::draw(sf::RenderWindow& window) {
    window.draw(this->get_sprite());
}

HealthBar::HealthBar(
    const sf::Vector2f& size,
    const sf::Vector2f& displacement,
    const sf::Color& background_color,
    const sf::Color& fill_color
)
: _size(size), _displacement(displacement) {
    background.setSize(size);
    background.setFillColor(background_color);
    background.setOutlineThickness(1.f);
    background.setOutlineColor(sf::Color::Black);

    fill.setSize(size);
    fill.setFillColor(fill_color);
}

void HealthBar::set_sprite_position(const sf::Vector2f& position) {
    background.setPosition(position+_displacement);
    fill.setPosition(position+_displacement);
}

void HealthBar::set_ratio(float ratio) {
    fill.setSize(sf::Vector2f(_size.x * ratio, _size.y));
}

void HealthBar::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(fill);
}

RombTank::RombTank(
    std::unique_ptr<Controller> controller,
    sf::Vector2f position,
    float angle,
    int team
) : DynamicObject(std::move(controller), position, angle), 
    healtbar(
        HealthBar(
            sf::Vector2f(50.f, 5.f),
            sf::Vector2f(-25.f, 20.f),
            sf::Color(100, 100, 100),
            sf::Color::Green
        )
    ) 
{
    LOG_TRACE();

    int sprite_pixel_length = 32;
    _speed = ROMB_TANK_SPEED;
    _max_health = ROMB_TANK_MAX_HEALTH;
    _health = _max_health;
    _team = team;
    _direction = angle_to_direction(angle);
    _sprite.setTexture(textures::romb_tank_texture);
    _sprite.setTextureRect(sf::IntRect(0, 0, sprite_pixel_length, sprite_pixel_length));
    _sprite.setOrigin(sprite_pixel_length/2, sprite_pixel_length/2);
    _cooldown = 1.0f;
    _cooldown_timer = 0.0f;
    _barrel_displacement_from_sprite_center = {float(sprite_pixel_length/2), 0.0f};
    healtbar.set_sprite_position(position);
}

RombTank::RombTank(
    std::unique_ptr<Controller> controller,
    sf::Vector2f position,
    float angle
) : RombTank(std::move(controller), position, angle, -1) {}

RombTank::RombTank(
    std::unique_ptr<Controller> controller,
    sf::Vector2f position
) : RombTank(std::move(controller), position, 0.0f, -1) {}

float RombTank::get_speed() const {
    return _speed;
}

sf::Vector2f RombTank::get_direction() const {
    return _direction;
};

void RombTank::set_direction(sf::Vector2f direction) {
    _direction = direction;
};

void RombTank::set_position(const sf::Vector2f& position) {
    _position = position;
    healtbar.set_sprite_position(position);
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

void RombTank::shoot(Scene& container) {
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
                ROMB_TANK_SHELL_LIFETIME,
                _team
            )
        );
        _cooldown_timer = _cooldown;
    }
}

void RombTank::take_damage(float damage) {
    LOG_TRACE();

    _health -= damage;
    if (_health <= 0) {
        set_terminate(); // Destroy the tank
    } else {
        healtbar.set_ratio(_health / ROMB_TANK_MAX_HEALTH);
    }
}

void RombTank::draw(sf::RenderWindow& window) {
    window.draw(this->get_sprite());
    if (_health < ROMB_TANK_MAX_HEALTH && 0 < _health) {
        healtbar.draw(window);
    }
}

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

void Shell::draw(sf::RenderWindow& window) {
    window.draw(this->get_sprite());
}