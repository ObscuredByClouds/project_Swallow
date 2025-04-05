#include "views.hpp"
#include <algorithm>
#include <cmath>

void view_follow_target(sf::View& view, DynamicObject& target) {
    float x_offset = target.get_position().x - view.getCenter().x;
    float y_offset = target.get_position().y - view.getCenter().y;
    auto smooth_follow = [](float i){
        float sign = std::copysign(1.0f, i);
        i = std::max(0.f, std::abs(i) - 25);
        i = i*std::min(i/50, 1.0f);
        i = copysign(i, sign);
        return i;
    };
    view.move(smooth_follow(x_offset), smooth_follow(y_offset));
}