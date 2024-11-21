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
        float _angle;
        sf::Sprite _sprite;

    public:

        ControlledObject(std::unique_ptr<Controller> controller,const sf::Vector2f &position);

        // position
        sf::Vector2f get_position() const;
        void         set_position(const sf::Vector2f& position);

        // texture rectangle (for animation)
        void set_texture_rectangle(const sf::IntRect& rectangle);

        // sprite management
        sf::Sprite get_sprite() const;
        void       set_sprite(sf::Texture& texture);
        void set_sprite_rotation(float angle);
        void set_sprite_position(const sf::Vector2f& position);

        // angle management
        float get_angle() const;
        void  set_angle(float new_angle);

        void update(float time) override;

        // pure virtual functions for convinience
        virtual float get_speed() const = 0;

        // unused stuff
        // void setController(std::unique_ptr<Controller> controller) {};
};