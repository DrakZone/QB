#include "WindowUtils.h"
#include "D3D.h"
#include "Game.h"
#include "GeometryBuilder.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;



void Game::Initialise()
{
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
	mBox.GetScale() = Vector3(0.5,0.5,0.5);
	Material& matB = mBox.GetMesh().GetSubMesh(0).material;
	matB.gfxData.Set(Vector4(2.2f, 2.2f, 2.2f, 1), Vector4(1.2f, 1.2f, 1.2f, 1), Vector4(0.9f, 0.8f, 0.8f, 1));
	matB.pTextureRV = d3d.GetCache().LoadTexture(&d3d.GetDevice(), "wall.dds");
	matB.texture = "wall.dds";

	enemy.initialise(d3d);

	d3d.GetFX().SetupDirectionalLight(0, true, Vector3(-0.7f, -0.7f, 0.7f), Vector3(0.47f, 0.47f, 0.47f), Vector3(0.15f, 0.15f, 0.15f), Vector3(0.25f, 0.25f, 0.25f));
	this->sMKIn.Initialise(WinUtil::Get().GetMainWnd());

}

void Game::Release()
{
}

void Game::Update(float dTime)
{		
	
	Vector3 pos = mBox.GetPosition();
		if (Game::sMKIn.IsPressed(VK_W))
			pos.z += velocity * SPEED * dTime ;
		else if (Game::sMKIn.IsPressed(VK_S))
			pos.z -= velocity * SPEED * dTime;
		if (Game::sMKIn.IsPressed(VK_D))
			pos.x += velocity * SPEED * dTime;
		else if (Game::sMKIn.IsPressed(VK_A))
			pos.x -= velocity * SPEED * dTime;

		if (pos.x >= 59.4) {
			pos.x = 59.4;
		}
		if (pos.x <= -59.4) {
			pos.x = -59.4;
		}
		if (pos.z >= 59.4) {
			pos.z = 59.4;
		}
		if (pos.z <= -59.4) {
			pos.z = -59.4;
		}
		

	mBox.SetPosition(pos);

	enemy.update(dTime);

}

void Game::Render(float dTime)
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	d3d.BeginRender(Colours::Black);

	float alpha = 0.5f + sinf(gAngle * 2)*0.5f;

	Vector3 camTgt(mBox.GetPosition());
	Vector3 camPos(camTgt.x, camTgt.y + 20, camTgt.z);

	d3d.GetFX().SetPerFrameConsts(d3d.GetDeviceCtx(), camPos);

	CreateViewMatrix(d3d.GetFX().GetViewMatrix(), camPos, camTgt, Vector3(0, 0, 1));
	CreateProjectionMatrix(d3d.GetFX().GetProjectionMatrix(), 0.25f*PI, WinUtil::Get().GetAspectRatio(), 1, 1000.f);

	//main cube 
	d3d.GetFX().Render(mBox);

	//floor
	d3d.GetFX().Render(mQuad);

	enemy.render(d3d);

	d3d.EndRender();

	sMKIn.PostProcess();
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
		case 'q':
		case 'Q':
			PostQuitMessage(0);
			return 0;
		}
	}
	//default message handling (resize window, full screen, etc)
	return WinUtil::Get().DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

