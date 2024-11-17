#pragma once

#include "objects.hpp"
#include "constants.hpp"
#include "controllers.hpp"
#include "textures.hpp"

//class Controller;  // Forward declaration

class RombTank : public ControlledObject {

protected:

    float speed;
    float health;
    float max_health;

public:

    RombTank(std::unique_ptr<Controller> controller, sf::Vector2f position);
    float get_speed();
};