#include "textures.hpp"

namespace textures {
    sf::Texture romb_tank_texture; // Определение

    void set_textures() {
        if (!romb_tank_texture.loadFromFile("./textures/romb_tank.png")) {
            // Обработка ошибки загрузки текстуры
        }
    }
}
