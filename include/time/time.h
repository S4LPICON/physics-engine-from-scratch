#pragma once

class Time {
public:
    static void update();

    static float deltaTime();

private:
    static float dt;
};