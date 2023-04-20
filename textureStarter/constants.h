#pragma once
#include "D3DUtil.h"

#include <string>   // for std::string
#include <math.h>

unsigned const SCREEN_WIDTH = 1920u;
unsigned const SCREEN_HEIGHT = 1080u;

unsigned const PlayingFieldWidth = 120u;
unsigned const PlayingFieldHeight = 120u;

// player
float const PlayerSpeed = 300.0;

// resources
unsigned const NumberResources = 50;
int const ResourcesSpawnRate = 1;
float const ResourcesRotationSpeed = 0.5f;

//Enemy
float const EnemyMovementSpeed = 50.0;
float const EnemySpeedRotation = PI * 2.0;
int const EnemySpawnRate = 1;
unsigned const NumberOfEnemy = 20;

//struct vector3
//{
//	double x;
//	double y;
//	double z;
//};

void seed();

float random_getd(float min, float max);