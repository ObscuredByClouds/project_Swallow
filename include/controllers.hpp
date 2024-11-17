#pragma once

#include "objects.hpp"
#include "constants.hpp"
#include "game_objects.hpp"

class Controller {

public:
    virtual ~Controller() = default;

    virtual void update(ControlledObject& object, float time) = 0;
};

/* class ZeroController : public Controller {
public:
    void update(ControlledObject& object, float time) {}
};

class RandomController : public Controller {
public:
    void update(ControlledObject& object, float time) {}
};

class AIController : public Controller {
public:
    void update(ControlledObject& object, float time) {}
};
 */
class RombTankInputController : public Controller {

public:

    void update(ControlledObject& object, float time) override;
};