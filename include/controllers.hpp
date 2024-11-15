#pragma once

#include "objects.hpp"
#include "constants.hpp"

class Controller {

public:
    virtual ~Controller() = default;
    virtual void update(ControlledObject& object, float time) = 0;
};

class ZeroController : public Controller {
public:
    void update(ControlledObject& object, float time) override {
        // Do nothing
    }
};

class RandomController : public Controller {
public:
    void update(ControlledObject& object, float time) override {
        // Random behavior
    }
};

class AIController : public Controller {
public:
    void update(ControlledObject& object, float time) override {
        // AI Logic
    }
};

class TankInputController : public Controller {

public:

    void update(ControlledObject& object, float time) override {
        sf::Vector2f position_updated = object.get_position();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            position_updated.x -= object.get_speed() * time;
            // object->set_angle();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            position_updated.x += object.get_speed() * time;
            // object->set_angle();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            position_updated.y -= object.get_speed() * time;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            position_updated.y += object.get_speed() * time;
        }

        object.set_position(position_updated);
    }
};