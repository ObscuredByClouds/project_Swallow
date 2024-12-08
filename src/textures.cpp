#include "textures.hpp"
#include <filesystem>

namespace textures {
    sf::Texture romb_tank_texture;
    
    void set_textures() {
        std::filesystem::path relativePathToTexture = "./textures/romb_tank.png";
        if (!romb_tank_texture.loadFromFile(relativePathToTexture.native())) { /* LOG_ERROR(); */ }
    }
}
