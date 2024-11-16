#pragma once

#include "objects.hpp"
#include "constants.hpp"
#include "controllers.hpp"
#include "textures.hpp"

class RombTank : public ControlledObject {

protected:

    float speed;
    float health;
    float max_health;

public:

    RombTank(
        std::unique_ptr<Controller> controller,
        const sf::Vector2f &position
    ) : ControlledObject(std::move(controller), position) {
        speed = ROMB_TANK_SPEED;
        max_health = ROMB_TANK_MAX_HEALTH;
        health = max_health;
        _sprite.setTexture(textures::romb_tank_texture);
    }

    float get_speed() {
        return speed;
    }

};