#pragma once

#include "objects.hpp"
#include "constants.hpp"
#include "controllers.hpp"
#include "textures.hpp"
#include <memory>

class RombTank : public ControlledObject {

private:

    float _speed;
    float _health;
    float _max_health;
    float _cooldown;
    float _cooldown_timer;

public:

    RombTank(std::unique_ptr<Controller> controller, sf::Vector2f position);

    float get_speed() const override;

    void shoot(ControlledObjectsContainer& container);

    float get_cooldown() const;

    float get_cooldown_timer() const;
    void set_cooldown_timer(float new_time);
    void decrement_cooldown_timer(float time);
};

class Shell : public ControlledObject {

private:

    float _speed;
    float _damage;
    float _lifetime;

public:

    Shell(std::unique_ptr<Controller> controller, sf::Vector2f position, float angle, float speed, float damage, float lifetime);
    ~Shell();

    float get_speed() const override;

    float get_damage() const;

    float get_lifetime() const;
};