#pragma once
#include "D3DUtil.h"

#include <string>   // for std::string
#include <math.h>

unsigned const SCREEN_WIDTH = 1280u;
unsigned const SCREEN_HEIGHT = 720u;

unsigned const PlayingFieldWidth = 120u;
unsigned const PlayingFieldHeight = 120u;

// player
float const PlayerSpeed = 300.0;

// resources
unsigned const NumberResources = 1u << 10;

float const EnemyMovementSpeed = 100.0;

float const EnemySpeedRotation = PI * 2.0;
int const EnemySpawnRate = 2;

unsigned const NumberOfEnemy = 10;

struct vector4
{
	double x;
	double y;
	double z;
	double w;
};

void seed();

float random_getd(float min, float max);