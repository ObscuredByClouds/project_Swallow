#pragma once

#include "objects.hpp"
#include "constants.hpp"
#include "controllers.hpp"
#include "textures.hpp"
#include <memory>

class RombTank : public ControlledObject {

private:

    float _speed;
    float _health;
    float _max_health;

public:

    RombTank(std::unique_ptr<Controller> controller, sf::Vector2f position);

    float get_speed() const override;

};