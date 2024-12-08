#include "utilities/math_helpers.hpp"

sf::Vector2f angle_to_direction(float angle) {
    return sf::Vector2f(std::cos(angle), std::sin(angle));
}

float direction_to_angle(const sf::Vector2f& direction) {
    return std::atan2(direction.y, direction.x);
}