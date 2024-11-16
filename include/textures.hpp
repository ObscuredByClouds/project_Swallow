#pragma once

#include <SFML/Graphics.hpp>

namespace textures {
    sf::Texture romb_tank_texture;

    static void set_textures() {
        romb_tank_texture.loadFromFile("./textures/romb_tank.png");
    }
}