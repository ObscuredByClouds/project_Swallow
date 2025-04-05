#pragma once

#include <cmath>
#include <random>

#include "constants.hpp"
#include "abstract_objects.hpp"
#include "game_objects.hpp"
#include "utilities/math_helpers.hpp"
#include "utilities/log.hpp"

class Controller {

public:
    virtual ~Controller() = default;

    virtual void update(DynamicObject& object, float time) = 0;
};
    
class ZeroController : public Controller {

public:
    void update(DynamicObject& object, float time) override;

};

/* class AIController : public Controller {
public:
    void update(DynamicObject& object, float time) override;
}; */
