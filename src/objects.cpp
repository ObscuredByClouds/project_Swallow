#pragma once

#include <SFML/Graphics.hpp>
#include "objects.hpp"

Object::~Object() {};

void Object::set_position(sf::Vector2f &new_position) {
    position = new_position;
};

void Object::set_angle(float new_angle) {
    angle = new_angle;
};

sf::Vector2f Object::get_position() const {
    return position;
};

float Object::get_angle() const {
    return angle;
};

sf::Sprite Object::get_sprite() const {
    return sprite;
};