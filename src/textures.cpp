#include "textures.hpp"
#include <filesystem>

namespace textures {
    sf::Texture axis_texture;
    sf::Texture romb_tank_texture;
    sf::Texture romb_tank_shell_texture;

    
    void set_textures() {
        std::filesystem::path relativePathToTextureRomb_tank = "./textures/romb_tank.png";
        std::filesystem::path relativePathToTextureTank_shell = "./textures/romb_tank_shell.png";
        std::filesystem::path relativePathToTextureAxis = "./textures/axis.png";
        if (!romb_tank_texture.loadFromFile(relativePathToTextureRomb_tank.native())) { /* LOG_ERROR(); */ }
        if (!romb_tank_shell_texture.loadFromFile(relativePathToTextureTank_shell.native())) { /* LOG_ERROR(); */ }
        if (!axis_texture.loadFromFile(relativePathToTextureAxis.native())) { /* LOG_ERROR(); */ }
    }
}
