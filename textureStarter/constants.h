#pragma once

#include <string>   // for std::string
#include <math.h>

unsigned const SCREEN_WIDTH = 1280u;
unsigned const SCREEN_HEIGHT = 720u;

unsigned const PlayingFieldWidth = 120u;
unsigned const PlayingFieldHeight = 120u;

const double PI = 3.141592653589793238463;
const float  PI_F = 3.14159265358979f;

// player
float const PlayerSpeed = 300.0;

// resources
unsigned const NumberResources = 1u << 10;

float const EnemyMovementSpeed = 100.0;

float const  EnemySpeedRotation = PI_F * 2.0;
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