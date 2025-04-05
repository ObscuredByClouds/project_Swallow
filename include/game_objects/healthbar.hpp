#pragma once

#include "game_objects_common.hpp"

class HealthBar : public Object {

    private:
    
        sf::Vector2f _size;
        sf::Vector2f _displacement;
        sf::RectangleShape _background;
        sf::RectangleShape _fill;
    
    public:
    
        HealthBar(
            const sf::Vector2f& size,
            const sf::Vector2f& displacement,
            const sf::Color& background_color,
            const sf::Color& fill_color
        );
    
        void set_sprite_position(const sf::Vector2f& position);
    
        void set_ratio(float ratio);
    
        void draw(sf::RenderWindow& window) override;
    };
    