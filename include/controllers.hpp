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
    void update(ControlledObject& object, float time) override;
};

class RandomController : public Controller {
public:
    void update(ControlledObject& object, float time) override;
};

class AIController : public Controller {
public:
    void update(ControlledObject& object, float time) override;
}; */

class RombTankInputController : public Controller {

protected:

    float elapsed_time;
    int frame_width;
    int frame_height;
    int n_frames;
    float frame_duration;
    int current_frame;

public:

    RombTankInputController();

    void update(ControlledObject& object, float time) override;
};