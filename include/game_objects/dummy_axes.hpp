#pragma once

#include "game_objects_common.hpp"

class DummyAxis : public DynamicObject {

    public:
    
        DummyAxis(std::unique_ptr<Controller> controller, sf::Vector2f position);
        float get_speed() const override {return 0.0f;}; // TODO should not be here. It`s because DynamicObject must have get_speed.
        void draw(sf::RenderWindow& window) override;
    };