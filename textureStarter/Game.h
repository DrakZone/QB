#ifndef GAME_H
#define GAME_H

#include "Mesh.h"
#include "Model.h"
#include "singleton.h"
#include "Input.h"
#include "Enemy.h"
#include "Resources.h"
#include "Score.h"

class Game : public Singleton<Game>
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
	const Vector3 GetPosition();
	void SetPosition(Vector3 pos);
	void on_collision();
	LRESULT WindowsMssgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	MouseAndKeys& GetMKIn() {
		return sMKIn;
	}

	Model mBox, mQuad;

private:

	Vector3 Position;
	float gAngle = 0;
	MouseAndKeys sMKIn;
	const float SPEED = 25;
	float velocity = 1;
};

#endif
