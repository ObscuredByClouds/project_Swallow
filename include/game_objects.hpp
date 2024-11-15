#pragma once

#include "objects.hpp"
#include "constants.hpp"
#include "controllers.hpp"

class RombTank : public ControlledObject {

protected:

    float speed;
    float health;
    float max_health;

public:

    RombTank(std::unique_ptr<Controller> controller)
        : _controller(std::move(controller)) {}
    
    RombTank(std::unique_ptr<Controller> controller)
    {
        _controller = std::move(controller);
    }

    void update(float time) override = 0;

};