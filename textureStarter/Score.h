#pragma once
#include <string>
#include <d3d11.h>
#include <iostream>	

#include "SpriteFont.h"
#include "D3D.h"
#include "D3DUtil.h"
#include "SimpleMath.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;


class Score
{
public:
	void initialise();
	int getAmount() const;
	void updateAmount(int);
private:
	int amount_ = 0;
	int value = 1;
};

class Font
{
public:
	void Initiallise(MyD3D& d3d);
	void Erase();
	void Print();
	void MainMenu(char* mainMenu, Vector2 position);
	void GameOver(char* gameOver, Vector2 position_2);

private:
	MyD3D* md3d = nullptr;	//our master

    Vector2 Origin = { 0, 0 };
	float Scale = 1.5;
	DirectX::SpriteFont* pSpriteFont = nullptr;
	DirectX::SpriteBatch* pSpriteBatch = nullptr;
	const char* score_;

	char* mainMenu;
	Vector2 position;

	char* gameOver;
	Vector2 position_2;

};