#pragma once

#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include <memory>

class Controller;

class Object {

    public:
    
        virtual ~Object() = default;
    
        virtual void draw(sf::RenderWindow& window) = 0;
    };
    