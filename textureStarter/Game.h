#ifndef GAME_H
#define GAME_H

#include "Mesh.h"
#include "Model.h"
#include "singleton.h"
#include "Input.h"
#include "Enemy.h"
#include "Resources.h"
#include "Score.h"

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
	Vector3 GetPosition();
	void SetPosition(Vector3 pos);
	void on_collision();
	LRESULT WindowsMssgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	MouseAndKeys& GetMKIn() {
		return sMKIn;
	}

	Model mBox, mQuad;

private:

	Vector3 Position;
	Enemy enemy;
	Resources resources;
	Score score;
	Font font;
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
