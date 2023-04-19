#pragma once

#include "constants.h"

struct Enemy
{
    vector4 position[NumberOfEnemy];
    vector4 velocity[NumberOfEnemy];
    bool isAlive[NumberOfEnemy];

    void initialise();
    void update(double elapsed);
    void render();
    void spawnEnemy();

    void on_collision(int index);
};

