#include "controllers.hpp"
#include <iostream>

RombTankInputController::RombTankInputController() : elapsed_time(0.0),
    frame_width(32), frame_height(32), n_frames(9), frame_duration(0.11), current_frame(0) {};
    
void RombTankInputController::update(ControlledObject& object, float time) {
    auto* tank = dynamic_cast<RombTank*>(&object);
    if (!tank) return;
    sf::Vector2f position_updated = tank->get_position();

    elapsed_time += time;
    if (elapsed_time >= frame_duration) {
        // Переходим к следующему кадру
        current_frame = (current_frame + 1) % n_frames;

        // Вычисляем позицию нового кадра в текстуре
        int column = current_frame % 3;  // 3 - количество колонок в вашем спрайтшите
        int row = current_frame / 3;     // 3 - количество строк в вашем спрайтшите

        // Устанавливаем новый прямоугольник текстуры
        object.set_texture_rectangle(sf::IntRect(column * frame_width, row * frame_height, frame_width, frame_height));

        // Сбрасываем накопленное время
        elapsed_time -= frame_duration;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        position_updated.x -= tank->get_speed() * time;
        // tank->set_angle();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        std::cout << "dx " << tank->get_speed() * time << std::endl;
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