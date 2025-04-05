#pragma once

#include "game_objects_common.hpp"

class RombTank : public DynamicObject {

    private:
    
        float _speed;
        float _health;
        float _max_health;
        float _cooldown;
        float _cooldown_timer;
        sf::Vector2f _direction;
        sf::Vector2f _barrel_displacement_from_sprite_center;
        int _team; // Team identifier
        HealthBar healtbar;
    
    public:
    
        RombTank(std::unique_ptr<Controller> controller, sf::Vector2f position);
        RombTank(std::unique_ptr<Controller> controller, sf::Vector2f position, float angle);
        RombTank(std::unique_ptr<Controller> controller, sf::Vector2f position, float angle, int team);
        
        float get_speed() const override;
    
        sf::Vector2f get_direction() const;
        void set_direction(sf::Vector2f direction);
    
        void set_position(const sf::Vector2f& position) override;
        void shoot(Scene& container);
    
        float get_cooldown() const;
        float get_cooldown_timer() const;
        void set_cooldown_timer(float new_time);
        void decrement_cooldown_timer(float time);
    
        float get_health() const { return _health; }
        float get_max_health() const { return _max_health; }
    
        int get_team() const { return _team; }
        void take_damage(float damage);
    
        void draw(sf::RenderWindow& window) override;
    };