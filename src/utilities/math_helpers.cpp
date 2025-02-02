#include "utilities/math_helpers.hpp"

sf::Vector2f angle_to_direction(float angle) {
    return sf::Vector2f(std::cos(angle), std::sin(angle));
}

float direction_to_angle(const sf::Vector2f& direction) {
    return std::atan2(direction.y, direction.x);
}

bool check_collision(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
    return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());
}