#pragma once

#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include <memory>

class Controller;

class Object {

public:

    virtual ~Object() = default;

    virtual void update(float time) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};

class DynamicObject : public Object {

    protected:

        std::unique_ptr<Controller> _controller;
        sf::Vector2f _position;
        float _angle;
        sf::Sprite _sprite;
        bool _terminate = false;

    public:

        DynamicObject(std::unique_ptr<Controller> controller, const sf::Vector2f &position, const float &angle);
        virtual ~DynamicObject();

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

        // spawn/despawn management
        bool get_terminate() const;
        void set_terminate();

        // scene utilities
        void update(float time) override;
        void draw(sf::RenderWindow& window) override;

        // pure virtual functions for convinience
        virtual float get_speed() const = 0;

        // unused stuff
        // void setController(std::unique_ptr<Controller> controller) {};
};

class Scene {

private:

    std::vector<std::unique_ptr<DynamicObject>> _objects;

private:

    Scene() = default;
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

public:

    static Scene& getInstance();

    void add_object(std::unique_ptr<DynamicObject> object);

    DynamicObject& operator[](size_t index);

    void update(float time);

    void draw(sf::RenderWindow& window);
};
