#pragma once

#include "game_objects_common.hpp"

class Shell : public DynamicObject {

    private:
    
        float _speed;
        float _damage;
        float _lifetime;
        int _team;
    
    public:
    
        Shell(std::unique_ptr<Controller> controller, sf::Vector2f position, float angle, float speed, float damage, float lifetime, int team);
        ~Shell();
    
        float get_speed() const override;
    
        float get_damage() const;
    
        float get_lifetime() const;
    
        int get_team() const { return _team; }
    
        void draw(sf::RenderWindow& window) override;
    };
    