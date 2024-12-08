#pragma once

#include <cmath>
#include <random>

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
}; */

/* class AIController : public Controller {
public:
    void update(ControlledObject& object, float time) override;
}; */

class RombTankController : public Controller {

private:
    // animation parameters, common for every RombTank
    float elapsed_time;
    int frame_width;
    int frame_height;
    int n_frames;
    float frame_duration;
    int current_frame;

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
    std::random_device random_device;
    std::mt19937 generator;
    std::uniform_real_distribution<> distribution;
    float random_behavior_elapsed_time;
    sf::Vector2f direction;
    bool moving_flag;

public:
    RandomRombTankController();

    void update(ControlledObject& object, float time) override;
};


// RombTank Input controller
class InputRombTankController : public RombTankController {

private:
    sf::RenderWindow& _window;

private:

    void updateRotation(ControlledObject& object);
    void updatePosition(ControlledObject& object, float time);

public:

    InputRombTankController(sf::RenderWindow& window);
    void update(ControlledObject& object, float time) override;

};