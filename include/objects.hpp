#pragma once

#include <SFML/Graphics.hpp>
#include "constants.hpp"

class Object {

protected:
    sf::Vector2f position;
    float angle;
    sf::Sprite sprite;

public:
    virtual ~Object();

    virtual void update(float time) = 0;

    void set_position(sf::Vector2f &new_position);
    void set_angle(float new_angle);

    sf::Vector2f get_position() const;
    float get_angle() const;
    sf::Sprite get_sprite() const;
};