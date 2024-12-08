#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

sf::Vector2f angle_to_direction(float angle);
float direction_to_angle(const sf::Vector2f& direction);