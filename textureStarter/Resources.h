#pragma once
#include "constants.h"
#include "GeometryBuilder.h"
#include "Mesh.h"
#include "Model.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Resources 
{
public:
    void initialise(MyD3D& d3d);
    void update(float elapsed);
    void render(MyD3D& d3d);
    void spawnResources();
    void reset();

    void on_collision();

private:

    Model resources;
    float spinAngle = 0;
    Vector3 position[NumberResources];
    bool isEaten[NumberResources];

};