#pragma once

#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include <memory>

class Controller;

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

        void set_sprite(sf::Texture& texture);

        void set_position(sf::Vector2f &position);

        void set_sprite_position(sf::Vector2f &position);
        /* void set_angle(float new_angle) {
            angle = new_angle;
        }; */

        sf::Sprite get_sprite() const;

        sf::Vector2f get_position() const;

        /* float get_angle() const {
            return angle;
        }; */

        ControlledObject(std::unique_ptr<Controller> controller,const sf::Vector2f &position);

        void update(float time) override;

        // void setController(std::unique_ptr<Controller> controller) {};
};