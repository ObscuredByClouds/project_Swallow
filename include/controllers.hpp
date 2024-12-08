#pragma once

#include <cmath>
#include <random>

#include "objects.hpp"
#include "constants.hpp"
#include "game_objects.hpp"
#include "utilities/math_helpers.hpp"

class Controller {

public:
    virtual ~Controller() = default;

    virtual void update(ControlledObject& object, float time) = 0;
};

class ZeroController : public Controller {
public:
    void update(ControlledObject& object, float time) override;
};

/* class AIController : public Controller {
public:
    void update(ControlledObject& object, float time) override;
}; */

class RombTankController : public Controller {

private:
    // animation parameters, common for every RombTank
    float _elapsed_time;
    int _frame_width;
    int _frame_height;
    int _n_frames;
    float _frame_duration;
    int _current_frame;

public:
    RombTankController();
    virtual ~RombTankController() = default;

    // animation functions, also common for every RombTank
    void updateAnimation(float time, ControlledObject& object);

    void updateTextureRectangle(ControlledObject& object);
};

// RombTank Random controller
class RandomRombTankController : public RombTankController {

private:
    std::random_device _random_device;
    std::mt19937 _generator;
    std::uniform_real_distribution<> _angle_distribution;
    float _random_behavior_elapsed_time;
    float _next_shot_elapsed_time;
    float _time_to_next_shot;
    bool _moving_flag;

public:
    RandomRombTankController();

    void update(ControlledObject& object, float time) override;
};


// RombTank Input controller
class InputRombTankController : public RombTankController {

private:
    sf::RenderWindow& _window;

private:

    void updateRotation(ControlledObject& object, float time);
    void updatePosition(ControlledObject& object, float time);

public:

    InputRombTankController(sf::RenderWindow& window);
    void update(ControlledObject& object, float time) override;

};


class ShellController : public Controller {

private:

    float _elapsed_time;

public:

    ShellController();

    virtual ~ShellController() = default;

    void update(ControlledObject& object, float time) override;
};
