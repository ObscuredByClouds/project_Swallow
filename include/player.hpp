#pragma once
#include "objects.hpp"
#include "player_controller.hpp"

enum class State {
    IDLE,
    RUN
};

class PlayerController;

class Player : public Object {

private:
    State             state;
    PlayerController* controller;

public:

    Player() = delete;
    Player(sf::Texture& texture, sf::Vector2f position_start, float health);
    ~Player();

    void update(float time) override;

    void set_state(State new_state);
};