#pragma once

#include <SFML/Graphics.hpp>

class Object {

protected:
    sf::Vector2f position;
    float angle;

public:
    virtual ~Object() = 0;

    virtual void update(float time) = 0;

    void take_damage(float damage);

    void set_position(sf::Vector2f &position);

    void set_direction(float angle);

    sf::Vector2f get_position() const;

    float get_вirection() const;
};