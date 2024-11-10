#pragma once

#include <SFML/Graphics.hpp>

namespace textures {
    sf::Texture player_texture;

    static void set_textures() {
        player_texture.loadFromFile("./textures/example_texture.png");
    }
}