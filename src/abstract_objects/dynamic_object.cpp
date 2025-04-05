#include "dynamic_object.hpp"

DynamicObject::DynamicObject(
    std::unique_ptr<Controller> controller,
    const sf::Vector2f &position,
    const float &angle
) : _controller(std::move(controller)), _position(position), _angle(angle) {}

DynamicObject::~DynamicObject() {}

// position
sf::Vector2f DynamicObject::get_position() const {return _position;};
void         DynamicObject::set_position(const sf::Vector2f& position) {_position = position;};

// texture rectangle (for animation)
void DynamicObject::set_texture_rectangle(const sf::IntRect& rectangle)
{_sprite.setTextureRect(rectangle);}

// sprite management
sf::Sprite DynamicObject::get_sprite() const {return _sprite;};
void       DynamicObject::set_sprite(sf::Texture& texture) {_sprite.setTexture(texture);};
void DynamicObject::set_sprite_rotation(float angle) {_sprite.setRotation(angle);};
void DynamicObject::set_sprite_position(const sf::Vector2f &position) {_sprite.setPosition(position);};

// angle management
float DynamicObject::get_angle() const {return _angle;};
void  DynamicObject::set_angle(float new_angle) {_angle = new_angle;};

// spawn/despawn management
bool DynamicObject::get_terminate() const {return _terminate;};
void DynamicObject::set_terminate() {_terminate = true;};

// common function for all dynamic objects
void DynamicObject::update(float time) {
    if (_controller) {
        _controller->update(*this, time);
    }
}