#pragma once

#include "controllers_common.hpp"

class ShellController : public Controller {

private:

    float _elapsed_time;

public:

    ShellController();

    virtual ~ShellController() = default;

    void update(DynamicObject& object, float time) override;
};
    