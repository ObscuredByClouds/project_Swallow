#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

sf::Vector2f angle_to_direction(float angle);
float direction_to_angle(const sf::Vector2f& direction);
bool check_collision(const sf::Sprite& sprite1, const sf::Sprite& sprite2);