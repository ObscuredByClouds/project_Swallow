#pragma once

#include "objects.hpp"
#include "constants.hpp"
#include "player.hpp"
#include "player_controller.hpp"

PlayerController* PlayerController::controller = nullptr;

PlayerController::~PlayerController() {
    delete controller;
}

PlayerController* PlayerController::get_object_controller() {
    if (!controller) {
        controller = new PlayerController();
    }
    return controller;
};

void PlayerController::control_object(Player* object, float time) {
    sf::Vector2f position_updated = object->get_position();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        position_updated.x -= PLAYER_SPEED * time;
        object->set_state(State::RUN);
        // object->set_angle();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        position_updated.x += PLAYER_SPEED * time;
        object->set_state(State::RUN);
        // object->set_angle();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        position_updated.y -= PLAYER_SPEED * time;
        // object->set_state(State::RUN);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        position_updated.y += PLAYER_SPEED * time;
        // object->set_state(State::RUN);
    }

    object->set_position(position_updated);
};