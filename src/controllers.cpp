#include "controllers.hpp"

void RombTankInputController::update(ControlledObject& object, float time) {
    auto* tank = dynamic_cast<RombTank*>(&object);
    if (!tank) return;
    sf::Vector2f position_updated = tank->get_position();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        position_updated.x -= tank->get_speed() * time;
        // tank->set_angle();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        position_updated.x += tank->get_speed() * time;
        // tank->set_angle();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        position_updated.y -= tank->get_speed() * time;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        position_updated.y += tank->get_speed() * time;
    }

    object.set_sprite_position(position_updated);
    object.set_position(position_updated);
}