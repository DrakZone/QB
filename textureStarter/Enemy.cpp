#include "Enemy.h"
#include "Game.h"

#include <cstdlib> // for std::memcpy, std::malloc, std::free
#include <math.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

extern Game game;

void Enemy::initialise(MyD3D& d3d)
{
    enemy.Initialise(BuildPyramid(d3d.GetMeshMgr()));
    enemy.GetScale() = Vector3(1, 1, 1);
    Material& matE = enemy.GetMesh().GetSubMesh(0).material;
    matE.gfxData.Set(Vector4(2.2f, 2.2f, 2.2f, 1), Vector4(1.2f, 1.2f, 1.2f, 1), Vector4(0.9f, 0.8f, 0.8f, 1));
    matE.pTextureRV = d3d.GetCache().LoadTexture(&d3d.GetDevice(), "wall.dds");
    matE.texture = "wall.dds";

    for (int counter = 0; counter < NumberOfEnemy; counter++)
    {
        isAlive[counter] = false;
    }
}

void Enemy::update(float elapsed)
{
    for (int counter = 0; counter < NumberOfEnemy; counter++) {
        // update position
        position[counter].x += EnemyMovementSpeed * velocity[counter].x * elapsed;
        position[counter].z += EnemyMovementSpeed * velocity[counter].z * elapsed;

        on_collision(counter);
        enemy.SetPosition(position[counter]);
    }

}

void Enemy::render(MyD3D& d3d)
{
    for (int counter = 0; counter < NumberOfEnemy; counter++) {
        if (isAlive[counter] == true) {
            enemy.GetPosition() = position[counter];
            Material matE = enemy.GetMesh().GetSubMesh(0).material;
            matE.gfxData.Set(Vector4(0.2f, 0.2f, 1.0f, 1), Vector4(1.2f, 1.2f, 1.2f, 1), Vector4(0.9f, 0.8f, 0.8f, 1));
            enemy.SetOverrideMat(&matE);
            d3d.GetFX().Render(enemy);
        }
    }
}

void Enemy::spawnEnemy()
{
    for (int counter = 0; counter < NumberOfEnemy; counter++) {
        if (isAlive[counter] == false) {
            float spawnrate = random_getd(0.0f, 15.0f);
            if (spawnrate <= EnemySpawnRate) {
                isAlive[counter] = true;
                position[counter].x = random_getd(PlayingFieldWidth / -2.1, PlayingFieldWidth / 2.1);
                position[counter].y = 1;
                position[counter].z = random_getd(PlayingFieldHeight / -2.1, PlayingFieldHeight / 2.1);

                velocity[counter].x = random_getd(-1.0, 1.0);
                velocity[counter].z = random_getd(-1.0, 1.0);

                double const magnitude = sqrt(velocity[counter].x * velocity[counter].x + velocity[counter].y * velocity[counter].y);
                velocity[counter].x /= magnitude;
                velocity[counter].y /= magnitude;
            }
        }
    }
}

void Enemy::on_collision(int index)
{
    if (position[index].x >= 60 || position[index].x <= -60) {
        velocity[index].x = -velocity[index].x;
    }
    if (position[index].z >= 60 || position[index].z <= -60) {
        velocity[index].z = -velocity[index].z;
    }
    if (position[index].x == game.GetPosition().x && position[index].z == game.GetPosition().z) {
        //GAME OVER
    }
}




