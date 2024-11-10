#include "player.hpp"
#include "player_controller.hpp"

Player::Player(sf::Texture& texture, sf::Vector2f position_start, float health)
{
    position = position_start;
    controller = PlayerController::get_object_controller();
    sprite.setTexture(texture);
}

Player::~Player() {}

void Player::update(float time) {
    state = State::IDLE;
    controller->control_object(this, time);

    if (state == State::RUN) {

    }
    else {

    }

    sprite.setPosition(position);
}

void Player::set_state(State new_state) {
    state = new_state;
}