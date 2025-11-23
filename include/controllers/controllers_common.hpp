#pragma once

#include <cmath>
#include <random>

#include "constants.hpp"
#include "abstract_objects.hpp"
#include "game_objects.hpp"
#include "utilities/math_helpers.hpp"
#include "utilities/log.hpp"

class Controller {

private:

    std::unique_ptr<DynamicObject> _controlled_object;

public:

    virtual ~Controller() = default;

    virtual void update(float time) = 0;
};
    
class ZeroController : public Controller {

public:
    void update(float time) override;

};

/* class AIController : public Controller {
public:
    void update(DynamicObject& object, float time) override;
}; */
