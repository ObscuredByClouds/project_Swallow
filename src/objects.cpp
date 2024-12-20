#include "objects.hpp"
#include "controllers.hpp"

ControlledObject::ControlledObject(
    std::unique_ptr<Controller> controller,
    const sf::Vector2f &position,
    const float &angle
) : _controller(std::move(controller)), _position(position), _angle(angle) {}

ControlledObject::~ControlledObject() {}

// position
sf::Vector2f ControlledObject::get_position() const {return _position;};
void         ControlledObject::set_position(const sf::Vector2f& position) {_position = position;};

// texture rectangle (for animation)
void ControlledObject::set_texture_rectangle(const sf::IntRect& rectangle)
{_sprite.setTextureRect(rectangle);}

// sprite management
sf::Sprite ControlledObject::get_sprite() const {return _sprite;};
void       ControlledObject::set_sprite(sf::Texture& texture) {_sprite.setTexture(texture);};
void ControlledObject::set_sprite_rotation(float angle) {_sprite.setRotation(angle);};
void ControlledObject::set_sprite_position(const sf::Vector2f &position) {_sprite.setPosition(position);};

// angle management
float ControlledObject::get_angle() const {return _angle;};
void  ControlledObject::set_angle(float new_angle) {_angle = new_angle;};

// spawn/despawn management
bool ControlledObject::get_terminate() const {return _terminate;};
void ControlledObject::set_terminate() {_terminate = true;};

// common function for all controlled objects
void ControlledObject::update(float time) {
    if (_controller) {
        _controller->update(*this, time);
    }
}

// unused stuff
/* void ControlledObject::setController(std::unique_ptr<Controller> controller) {
    _controller = std::move(controller);
} */

ControlledObjectsContainer& ControlledObjectsContainer::getInstance() {
    static ControlledObjectsContainer instance;
    return instance;
}

void ControlledObjectsContainer::add_object(std::unique_ptr<ControlledObject> object) {
    _objects.push_back(std::move(object));
}

ControlledObject& ControlledObjectsContainer::operator[](size_t index) {
    return *_objects[index];
}

void ControlledObjectsContainer::update(float time) {
    for (auto& object : _objects) {
        object->update(time);
    }

    _objects.erase(
        std::remove_if(_objects.begin(), _objects.end(), [](const std::unique_ptr<ControlledObject>& obj) {
            return obj->get_terminate();
        }),
        _objects.end()
    );
}

void ControlledObjectsContainer::draw(sf::RenderWindow& window) {
    for (const auto& object : _objects) {
        window.draw(object->get_sprite());
    }
}