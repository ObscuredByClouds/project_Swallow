#include "game_objects/dummy_axes.hpp"

DummyAxis::DummyAxis(
    std::unique_ptr<Controller> controller,
    sf::Vector2f position
) : DynamicObject(std::move(controller), position, 0.0f) {
    _sprite.setTexture(resources::axis_texture);
    _sprite.setPosition(position);
};

void DummyAxis::draw(sf::RenderWindow& window) {
    window.draw(this->get_sprite());
}