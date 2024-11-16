#pragma once

#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "controllers.hpp"

class Object {

public:

    virtual ~Object() = default;

    virtual void update(float time) = 0;

};

class ControlledObject : public Object {

    protected:

        std::unique_ptr<Controller> _controller;
        sf::Vector2f _position;
        //float angle;
        sf::Sprite _sprite;

    public:

        void set_sprite(sf::Texture& texture)
        {
            _sprite.setTexture(texture);
        };

        void set_position(sf::Vector2f &position)
        {
            _position = position;
        };

        /* void set_angle(float new_angle) {
            angle = new_angle;
        }; */

        sf::Sprite get_sprite() const {
            return _sprite;
        };

        sf::Vector2f get_position() const {
            return _position;
        };

        /* float get_angle() const {
            return angle;
        }; */

        ControlledObject(
            std::unique_ptr<Controller> controller,
            sf::Vector2f &position
        ) : _controller(std::move(controller)), _position(position) {}

        void update(float time) override {
            if (_controller) {
                _controller->update(*this, time);
            }
        }

        void setController(std::unique_ptr<Controller> controller) {
            _controller = std::move(controller);
        }
};