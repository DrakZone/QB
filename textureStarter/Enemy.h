#pragma once

#include "constants.h"
#include "D3D.h"
#include "GeometryBuilder.h"
#include "Mesh.h"
#include "Model.h"
#include "WindowUtils.h"

struct Enemy
{
    vector4 position[NumberOfEnemy];
    vector4 velocity[NumberOfEnemy];
    bool isAlive[NumberOfEnemy];

    void initialise(MyD3D& d3d);
    void update(float elapsed);
    void render(MyD3D& d3d);
    void spawnEnemy();

    void on_collision(int index);

    Model enemy;
};

