#pragma once

#include "objects.hpp"
#include "player.hpp"
#include "constants.hpp"

class Player;

class PlayerController {

private:
    PlayerController() = default;

    static PlayerController* controller;
  
public:

    PlayerController(PlayerController const&) = delete;

    void operator=(PlayerController const&) = delete;

    ~PlayerController();

    static PlayerController* get_object_controller();

    void control_object(Player* object, float time);
};