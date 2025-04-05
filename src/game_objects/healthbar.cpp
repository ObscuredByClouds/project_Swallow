#include "game_objects/healthbar.hpp"

HealthBar::HealthBar(
    const sf::Vector2f& size,
    const sf::Vector2f& displacement,
    const sf::Color& background_color,
    const sf::Color& fill_color
)
: _size(size), _displacement(displacement) {
    _background.setSize(size);
    _background.setFillColor(background_color);
    _background.setOutlineThickness(1.f);
    _background.setOutlineColor(sf::Color::Black);

    _fill.setSize(size);
    _fill.setFillColor(fill_color);
}

void HealthBar::set_sprite_position(const sf::Vector2f& position) {
    _background.setPosition(position+_displacement);
    _fill.setPosition(position+_displacement);
}

void HealthBar::set_ratio(float ratio) {
    _fill.setSize(sf::Vector2f(_size.x * ratio, _size.y));
}

void HealthBar::draw(sf::RenderWindow& window) {
    window.draw(_background);
    window.draw(_fill);
}