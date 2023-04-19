#ifndef GAME_H
#define GAME_H

#include "Mesh.h"
#include "Model.h"
#include "singleton.h"
#include "Input.h"
#include "Enemy.h"

class Game
{
public:
	Game() {}
	~Game() {
		Release();
	}
	void Update(float dTime);
	void Render(float dTime);
	void Initialise();
	void Release();
	LRESULT WindowsMssgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	MouseAndKeys& GetMKIn() {
		return sMKIn;
	}

	Model mBox, mQuad;

private:

	Enemy enemy;
	bool keypressed;
	float gAngle = 0;
	MouseAndKeys sMKIn;
	const float SPEED = 25;
	float velocity = 1;
	//DirectX::SimpleMath::Vector3 walls_rot[3] = {
	//	{0, 0, 0},
	//	{-1.57, 0, 0},
	//	{0, 0, -1.57}
	//};
	//DirectX::SimpleMath::Vector3 walls_pos[3] = {
	//	{0, -1, 0},
	//	{0, 2, 60},
	//	{-60, 2, 0}
	//};
};

#endif
