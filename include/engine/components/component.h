#pragma once

class Component {
public:
    virtual ~Component() = default;

    virtual void update(float dt) = 0;
};