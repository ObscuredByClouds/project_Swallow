#pragma once

#include "objects.hpp"
#include "constants.hpp"
#include "controllers.hpp"
#include "resources.hpp"
#include <memory>

#include "utilities/math_helpers.hpp"
#include "utilities/log.hpp"

class DummyAxis : public DynamicObject {

public:

    DummyAxis(std::unique_ptr<Controller> controller, sf::Vector2f position);
    float get_speed() const override {return 0.0f;}; // TODO should not be here. It`s because DynamicObject must have get_speed.
    void draw(sf::RenderWindow& window) override;
};

class HealthBar : public Object {

private:

    sf::Vector2f _size;
    sf::Vector2f _displacement;
    sf::RectangleShape _background;
    sf::RectangleShape _fill;

public:

    HealthBar(
        const sf::Vector2f& size,
        const sf::Vector2f& displacement,
        const sf::Color& background_color,
        const sf::Color& fill_color
    );

    void set_sprite_position(const sf::Vector2f& position);

    void set_ratio(float ratio);

    void draw(sf::RenderWindow& window) override;
};

class RombTank : public DynamicObject {

private:

    float _speed;
    float _health;
    float _max_health;
    float _cooldown;
    float _cooldown_timer;
    sf::Vector2f _direction;
    sf::Vector2f _barrel_displacement_from_sprite_center;
    int _team; // Team identifier
    HealthBar healtbar;

public:

    RombTank(std::unique_ptr<Controller> controller, sf::Vector2f position);
    RombTank(std::unique_ptr<Controller> controller, sf::Vector2f position, float angle);
    RombTank(std::unique_ptr<Controller> controller, sf::Vector2f position, float angle, int team);
    
    float get_speed() const override;

    sf::Vector2f get_direction() const;
    void set_direction(sf::Vector2f direction);

    void set_position(const sf::Vector2f& position) override;
    void shoot(Scene& container);

    float get_cooldown() const;
    float get_cooldown_timer() const;
    void set_cooldown_timer(float new_time);
    void decrement_cooldown_timer(float time);

    float get_health() const { return _health; }
    float get_max_health() const { return _max_health; }

    int get_team() const { return _team; }
    void take_damage(float damage);

    void draw(sf::RenderWindow& window) override;
};

class Shell : public DynamicObject {

private:

    float _speed;
    float _damage;
    float _lifetime;
    int _team;

public:

    Shell(std::unique_ptr<Controller> controller, sf::Vector2f position, float angle, float speed, float damage, float lifetime, int team);
    ~Shell();

    float get_speed() const override;

    float get_damage() const;

    float get_lifetime() const;

    int get_team() const { return _team; }

    void draw(sf::RenderWindow& window) override;
};

