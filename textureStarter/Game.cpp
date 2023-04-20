#include "WindowUtils.h"
#include "D3D.h"
#include "Game.h"
#include "GeometryBuilder.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

extern Score score;
extern Enemy enemy;
extern Resources resources;
extern Font font;

void Game::Initialise()
{
	seed();

	MyD3D& d3d = WinUtil::Get().GetD3D();
	//wood floor
	mQuad.Initialise(BuildQuad(d3d.GetMeshMgr()));
	mQuad.GetRotation() = Vector3(0, 0, 0);
	mQuad.GetScale() = Vector3(3*20, 1*20, 3*20);
	mQuad.GetPosition() = Vector3(0, -1, 0);
	Material& matQ = mQuad.GetMesh().GetSubMesh(0).material;
	matQ.gfxData.Set(Vector4(1.2f, 1.2f, 1.2f, 1), Vector4(1.2f, 1.2f, 1.2f, 1), Vector4(0.9f, 0.8f, 0.8f, 1));
	matQ.pTextureRV = d3d.GetCache().LoadTexture(&d3d.GetDevice(), "tiles.dds");
	matQ.texture = "tiles.dds";

	//pandoras box
	mBox.Initialise(BuildCube(d3d.GetMeshMgr()));
	mBox.GetScale() = Vector3(1.2,1.2,1.2);
	mBox.GetPosition() = Vector3(0, 1, 0);
	Material& matB = mBox.GetMesh().GetSubMesh(0).material;
	matB.gfxData.Set(Vector4(0.2f, 0.2f, 0.2f, 1), Vector4(0.2f, 0.2f, 5.2f, 1), Vector4(0.9f, 0.8f, 0.8f, 1));
	//matB.pTextureRV = d3d.GetCache().LoadTexture(&d3d.GetDevice(), "wall.dds");
	//matB.texture = "wall.dds";

	enemy.initialise(d3d);
	resources.initialise(d3d);
	font.Initiallise(d3d);
	score.initialise();

	d3d.GetFX().SetupDirectionalLight(0, true, Vector3(-0.7f, -0.7f, 0.7f), Vector3(0.47f, 0.47f, 0.47f), Vector3(0.15f, 0.15f, 0.15f), Vector3(0.25f, 0.25f, 0.25f));
	this->sMKIn.Initialise(WinUtil::Get().GetMainWnd());


}

void Game::Release()
{
	font.Erase();
}

void Game::Update(float dTime)
{		
	switch (m_gameState)
	{
	case GameState::MainMenu:
	{
		if (Game::sMKIn.IsPressed(VK_RETURN))
		{
			SetGameState(GameState::Gameplay);
			score.initialise(); // Reset the player's score
			enemy.reset(); // Reset the enemy's state
			resources.reset(); // Reset the resource state
		}
		if (Game::sMKIn.IsPressed(VK_H))
		{
			SetGameState(GameState::HowToPlay);
		}
		if (Game::sMKIn.IsPressed(VK_Q))
		{
			PostQuitMessage(0);
		}
		break;
	}
	case GameState::HowToPlay:
	{
		if (Game::sMKIn.IsPressed(VK_BACK))
		{
			SetGameState(GameState::MainMenu);
		}
		if (Game::sMKIn.IsPressed(VK_Q))
		{
			PostQuitMessage(0);
		}
	}
	case GameState::Gameplay: {
		Vector3 pos = mBox.GetPosition();
		if (Game::sMKIn.IsPressed(VK_W))
			pos.z += velocity * SPEED * dTime;
		else if (Game::sMKIn.IsPressed(VK_S))
			pos.z -= velocity * SPEED * dTime;
		if (Game::sMKIn.IsPressed(VK_D))
			pos.x += velocity * SPEED * dTime;
		else if (Game::sMKIn.IsPressed(VK_A))
			pos.x -= velocity * SPEED * dTime;

		if (pos.x >= 58.5) {
			pos.x = 58.5;
		}
		if (pos.x <= -58.5) {
			pos.x = -58.5;
		}
		if (pos.z >= 58.5) {
			pos.z = 58.5;
		}
		if (pos.z <= -58.5) {
			pos.z = -58.5;
		}

		mBox.GetPosition() = pos;
		SetPosition(pos);

		enemy.update(dTime);
		resources.update(dTime);

		resources.spawnResources();
		if (score.getAmount() % 5) {
			enemy.spawnEnemy();
		}
		break;
	}
	case GameState::GameOver:
	{
		if (Game::sMKIn.IsPressed(VK_BACK))
		{
			SetGameState(GameState::MainMenu);
		}
		if (Game::sMKIn.IsPressed(VK_Q)) 
		{
			PostQuitMessage(0);
		}
		break;
	}
	}
}

void Game::Render(float dTime)
{
	switch (m_gameState)
	{
	case GameState::MainMenu:
	{
		MyD3D& d3d = WinUtil::Get().GetD3D();
		d3d.BeginRender(Colours::Black);

		// Draw some text on the screen
		font.MainMenu("Press Enter to start", Vector2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
		font.MainMenu("Press 'H' for How To Play", Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50));
		font.MainMenu("Press 'Q' To Quit", Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100));

		d3d.EndRender();
		break;
	}
	case GameState::HowToPlay:
	{
		MyD3D& d3d = WinUtil::Get().GetD3D();
		d3d.BeginRender(Colours::Black);

		font.MainMenu(" ---------WASD TO MOVE!-------- \n COLLECT RED TRIANGLE TO EARN POINTS! \n AVOID BLUE TRIANGLE! THEY KILL YOU!", Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		font.MainMenu("Press Q to quit! Press backspace to go back to main menu!", Vector2(SCREEN_WIDTH / 2 + 200, SCREEN_WIDTH / 3));

		d3d.EndRender();
		break;
	}
	case GameState::Gameplay:
	{
		MyD3D& d3d = WinUtil::Get().GetD3D();
		d3d.BeginRender(Colours::Black);

		float alpha = 0.5f + sinf(gAngle * 2) * 0.5f;

		Vector3 camTgt(mBox.GetPosition());
		Vector3 camPos(camTgt.x, camTgt.y + 40, camTgt.z);

		d3d.GetFX().SetPerFrameConsts(d3d.GetDeviceCtx(), camPos);

		CreateViewMatrix(d3d.GetFX().GetViewMatrix(), camPos, camTgt, Vector3(0, 0, 1));
		CreateProjectionMatrix(d3d.GetFX().GetProjectionMatrix(), 0.25f * PI, WinUtil::Get().GetAspectRatio(), 1, 1000.f);

		//floor
		d3d.GetFX().Render(mQuad);

		//main cube 
		d3d.GetFX().Render(mBox);

		enemy.render(d3d);
		resources.render(d3d);

		font.Print();

		d3d.EndRender();

		sMKIn.PostProcess();
		break;
	}
	case GameState::GameOver:
	{
		MyD3D& d3d = WinUtil::Get().GetD3D();
		d3d.BeginRender(Colours::Black);

		 //Draw some text on the screen
		font.GameOver("Game Over!", Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		font.GameOver("Press BackSpace to go Back to Main Menu", Vector2(SCREEN_WIDTH / 2 + 110, SCREEN_HEIGHT / 2 + 50));
		font.GameOver("Press Q to quit!", Vector2(SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 3 ));

		d3d.EndRender();
		break;
	}
	}

}

LRESULT Game::WindowsMssgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//do something game specific here
	switch (msg)
	{
		// Respond to a keyboard event.
	case WM_CHAR:
		switch (wParam)
		{
		case 27:
			PostQuitMessage(0);
			return 0;
		}
	}
	//default message handling (resize window, full screen, etc)
	return WinUtil::Get().DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

const Vector3 Game::GetPosition() { return Position; }
void Game::SetPosition(Vector3 pos) {
	Position = mBox.GetPosition();
}

void Game::on_collision() {
	score.updateAmount(1);
}

