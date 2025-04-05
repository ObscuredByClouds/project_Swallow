#pragma once

#include "abstract_objects.hpp"
#include "game_objects.hpp"

class Scene {

    private:
    
        std::vector<std::unique_ptr<DynamicObject>> _objects;
    
    private:
    
        Scene() = default;
        Scene(const Scene&) = delete;
        Scene& operator=(const Scene&) = delete;
    
    public:
    
        static Scene& getInstance();
    
        void add_object(std::unique_ptr<DynamicObject> object);
    
        DynamicObject& operator[](size_t index);
    
        void update(float time);
    
        void draw(sf::RenderWindow& window);
    };
    