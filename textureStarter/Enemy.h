#pragma once

#include "constants.h"
#include "D3D.h"
#include "GeometryBuilder.h"
#include "Mesh.h"
#include "Model.h"
#include "WindowUtils.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Enemy
{
private:
    Vector3 position[NumberOfEnemy];
    Vector3 velocity[NumberOfEnemy];
    bool isAlive[NumberOfEnemy];
    Model enemy;

public:
    void initialise(MyD3D& d3d);
    void update(float elapsed);
    void render(MyD3D& d3d);
    void spawnEnemy();

    void on_collision(int index);

};



