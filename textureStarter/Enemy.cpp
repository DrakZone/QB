#include "Enemy.h"

#include <cstdlib> // for std::memcpy, std::malloc, std::free
#include <math.h>

Enemy enemys;

//NEW CODE

void Enemy::initialise()
{
    for (int counter = 0; counter < NumberOfEnemy; counter++)
    {
        isAlive[counter] = false;
    }
}

void Enemy::update(double elapsed)
{
    for (int counter = 0; counter < NumberOfEnemy; counter++) {
        // update position
        position[counter].x += EnemyMovementSpeed * velocity[counter].x * elapsed;
        position[counter].z += EnemyMovementSpeed * velocity[counter].z * elapsed;

        on_collision(counter);

    }

}

void Enemy::render()
{
    for (int counter = 0; counter < NumberOfEnemy; counter++) {
        if (isAlive[counter] == true) {

        }
    }
}

void Enemy::spawnEnemy()
{
    for (int counter = 0; counter < NumberOfEnemy; counter++) {
        if (isAlive[counter] = false) {
            float spawnrate = random_getd(0.0f, 10.0f);
            if (spawnrate <= EnemySpawnRate) {
                isAlive[counter] = true;
                position[counter].x = random_getd(PlayingFieldWidth / -2.0, PlayingFieldWidth / 2.0);
                position[counter].y = 1;
                position[counter].z = random_getd(PlayingFieldHeight / -2.0, PlayingFieldHeight / 2.0);

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
    if (position[index].x >= 59 || position[index].x <= -59) {
        velocity[index].x = -velocity[index].x;
    }
    if (position[index].z >= 59 || position[index].z <= -59) {
        velocity[index].z = -velocity[index].z;
    }
    
}




