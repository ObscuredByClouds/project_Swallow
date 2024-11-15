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
    private:
        std::unique_ptr<Controller> _controller;

    protected:
        sf::Vector2f position;
        //float angle;
        sf::Sprite sprite;
        
    public:
        void set_sprite(sf::Texture& texture)
        {
            sprite.setTexture(texture);
        };

        void set_position(sf::Vector2f &new_position)
        {
            position = new_position;
        };

        /* void set_angle(float new_angle) {
            angle = new_angle;
        }; */

        sf::Sprite get_sprite() const {
            return sprite;
        };

        sf::Vector2f get_position() const {
            return position;
        };

        /* float get_angle() const {
            return angle;
        }; */

        ControlledObject(std::unique_ptr<Controller> controller)
            : _controller(std::move(controller)) {}

        void update(float time) override {
            if (_controller) {
                _controller->update(*this, time);
            }
        }

        void setController(std::unique_ptr<Controller> controller) {
            _controller = std::move(controller);
        }
};