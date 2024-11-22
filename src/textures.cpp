#include "textures.hpp"

namespace textures {
    sf::Texture romb_tank_texture;

    void set_textures() {
        if (!romb_tank_texture.loadFromFile("./textures/romb_tank.png")) { /* LOG_ERROR(); */ }
    }
}
