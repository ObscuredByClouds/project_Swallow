#include "scene/scene.hpp"

Scene& Scene::getInstance() {
    static Scene instance;
    return instance;
}

void Scene::add_object(std::unique_ptr<DynamicObject> object) {
    _objects.push_back(std::move(object));
}

DynamicObject& Scene::operator[](size_t index) {
    return *_objects[index];
}

void Scene::update(float time) {
    for (auto& object : _objects) {
        object->update(time);
    }

    // Check for collisions between shells and tanks
    // TODO: cathegorize objects (tanks/shells) or use Spatial Partitioning or use std::async
    for (size_t i = 0; i < _objects.size(); ++i) {
        if (_objects[i]->get_terminate()) continue;

        DynamicObject& obj1 = *_objects[i];
        if (dynamic_cast<Shell*>(&obj1)) {
            Shell* shell = dynamic_cast<Shell*>(&obj1);

            for (size_t j = 0; j < _objects.size(); ++j) {
                if (i == j || _objects[j]->get_terminate()) continue;

                DynamicObject& obj2 = *_objects[j];
                if (dynamic_cast<RombTank*>(&obj2)) {
                    RombTank* tank = dynamic_cast<RombTank*>(&obj2);

                    // Check if they belong to different teams
                    if (shell->get_team() != tank->get_team()) {
                        if (check_collision(shell->get_sprite(), tank->get_sprite())) {
                            tank->take_damage(shell->get_damage());
                            shell->set_terminate(); // Remove the shell
                            break;
                        }
                    }
                }
            }
        }
    }

    _objects.erase(
        std::remove_if(_objects.begin(), _objects.end(), [](const std::unique_ptr<DynamicObject>& obj) {
            return obj->get_terminate();
        }),
        _objects.end()
    );
}

// TODO: std::unique_ptr<Object>
void Scene::draw(sf::RenderWindow& window) {
    for (const std::unique_ptr<DynamicObject>& object : _objects) {
        object->draw(window);
    }
}