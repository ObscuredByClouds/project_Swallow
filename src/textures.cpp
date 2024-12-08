#include "textures.hpp"

namespace textures {
    sf::Texture axis_texture;
    sf::Texture romb_tank_texture;
    sf::Texture romb_tank_shell_texture;

    void set_textures() {
        if (!axis_texture.loadFromFile("./textures/axis.png")) { /* LOG_ERROR(); */ }
        if (!romb_tank_texture.loadFromFile("./textures/romb_tank.png")) { /* LOG_ERROR(); */ }
        if (!romb_tank_shell_texture.loadFromFile("./textures/romb_tank_shell.png")) { /* LOG_ERROR(); */ }
    }
}
