#include "resources.hpp"
#include <filesystem>
#include <iostream>
#include "utilities/get_executable_directory.hpp"

namespace resources {
    sf::Texture axis_texture;
    sf::Texture romb_tank_texture;
    sf::Texture romb_tank_shell_texture;
    sf::Font arial_font;

    void load_resources() {
        std::filesystem::path root = get_executable_directory();
        #define STRING(string) #string
        #define LOAD_TEXTURE(textureName) \
        if (!textureName##_texture.loadFromFile((root / STRING(../textures/textureName.png)).lexically_normal())) { /* LOG_ERROR(); */ }
        LOAD_TEXTURE(romb_tank)
        LOAD_TEXTURE(romb_tank_shell)
        LOAD_TEXTURE(axis)
        // if (!romb_tank_texture.loadFromFile((root / "../textures/romb_tank.png"))) { /* LOG_ERROR(); */ }
        // if (!romb_tank_shell_texture.loadFromFile((root / "../textures/romb_tank_shell.png"))) { /* LOG_ERROR(); */ }
        // if (!axis_texture.loadFromFile((root / "../textures/axis.png"))) { /* LOG_ERROR(); */ }
        if (!arial_font.loadFromFile((root / "../fonts/arial.ttf").lexically_normal())) { /* LOG_ERROR(); */ }
    }
}
