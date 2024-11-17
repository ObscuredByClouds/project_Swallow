#include "objects.hpp"
#include "controllers.hpp"

void ControlledObject::set_sprite(sf::Texture& texture)
{
    _sprite.setTexture(texture);
};

void ControlledObject::set_position(sf::Vector2f &position)
{
    _position = position;
};

void ControlledObject::set_sprite_position(sf::Vector2f &position)
{
    _sprite.setPosition(position);
};

/* void set_angle(float new_angle) {
    angle = new_angle;
}; */

sf::Sprite ControlledObject::get_sprite() const {
    return _sprite;
};

sf::Vector2f ControlledObject::get_position() const {
    return _position;
};

/* float get_angle() const {
    return angle;
}; */

ControlledObject::ControlledObject(
    std::unique_ptr<Controller> controller,
    const sf::Vector2f &position
) : _controller(std::move(controller)), _position(position) {}

void ControlledObject::update(float time) {
    if (_controller) {
        _controller->update(*this, time);
    }
}

/* void ControlledObject::setController(std::unique_ptr<Controller> controller) {
    _controller = std::move(controller);
} */