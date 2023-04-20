#include "Resources.h"
#include "Game.h"

#include <cstdlib> // for std::memcpy, std::malloc, std::free
#include <math.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

extern Game game;

void Resources::initialise(MyD3D& d3d)
{
    resources.Initialise(d3d.GetMeshMgr().GetMesh("pyramid"));// BuildPyramid(d3d.GetMeshMgr()));
    resources.GetScale() = Vector3(1, 1, 1);
    Material& matR = resources.GetMesh().GetSubMesh(0).material;
    matR.gfxData.Set(Vector4(2.2f, 2.2f, 2.2f, 1), Vector4(1.2f, 1.2f, 1.2f, 1), Vector4(0.9f, 0.8f, 0.8f, 1));
    matR.pTextureRV = d3d.GetCache().LoadTexture(&d3d.GetDevice(), "wall.dds");
    matR.texture = "wall.dds";

    for (int counter = 0; counter < NumberResources; counter++)
    {
        isEaten[counter] = true;
    }
    spawnResources();
}

void Resources::update(float elapsed)
{
    spinAngle += elapsed * 0.5f;
    resources.GetRotation().y = spinAngle;

    on_collision();
}

void Resources::render(MyD3D& d3d)
{
    for (int counter = 0; counter < NumberResources; counter++) {
        if (isEaten[counter] == false) {
            resources.GetPosition() = position[counter];
            Material matR = resources.GetMesh().GetSubMesh(0).material;
            matR.gfxData.Set(Vector4(1.0f, 0.1f, 0.0f, 1), Vector4(1.2f, 1.2f, 1.2f, 1), Vector4(0.9f, 0.8f, 0.8f, 1));
            resources.SetOverrideMat(&matR);
            d3d.GetFX().Render(resources);
        }
    }
}

void Resources::spawnResources()
{
    for (int counter = 0; counter < NumberResources; counter++) {
        if (isEaten[counter] == true) {
            float spawnrate = random_getd(0.0f, 50.0f);
            if (spawnrate <= ResourcesSpawnRate) {
                isEaten[counter] = false;
                position[counter].x = random_getd(PlayingFieldWidth / -2.1, PlayingFieldWidth / 2.1);
                position[counter].y = 1;
                position[counter].z = random_getd(PlayingFieldHeight / -2.1, PlayingFieldHeight / 2.1);
                resources.SetPosition(position[counter]);
            }
        }
    }
}


void Resources::on_collision()
{
    for (int counter = 0; counter < NumberResources; counter++) {
        if (isEaten[counter] == false) {
            float R_top_x = position[counter].x + 0.2;
            float R_bottom_x = position[counter].x - 0.2;
            float R_right_z = position[counter].z + 0.2;
            float R_left_z = position[counter].z - 0.2;

            float B_top_x = game.GetPosition().x + 0.5;
            float B_bottom_x = game.GetPosition().x - 0.5;
            float B_right_z = game.GetPosition().z + 0.5;
            float B_left_z = game.GetPosition().z - 0.5;

            if (R_top_x >= B_bottom_x && R_bottom_x <= B_top_x && R_right_z >= B_left_z && R_left_z <= B_right_z) {
                isEaten[counter] = true;
                game.on_collision();
            }
        }
    }
}