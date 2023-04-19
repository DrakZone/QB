#include "WindowUtils.h"
#include "D3D.h"
#include "Game.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Game* pGame = nullptr;

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//do something game specific here
	switch (msg)
	{
		// Respond to a keyboard event.
	case WM_CHAR:
		if (pGame)
		{
			return pGame->WindowsMssgHandler(hwnd, msg, wParam, lParam);
		}
	case WM_INPUT:
		if (pGame)
		{
			pGame->GetMKIn().MessageEvent((HRAWINPUT)lParam);
			break;
		}
	}
	return WinUtil::DefaultMssgHandler(hwnd, msg, wParam, lParam);
}



//main entry point for the game
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{

	int w(1024), h(768);
	if (!WinUtil::Get().InitMainWindow(w, h, hInstance, "Proj_1", MainWndProc, true))
		assert(false);

	MyD3D d3d;
	if (!d3d.InitDirect3D())
		assert(false);
	WinUtil::Get().SetD3D(d3d);
	d3d.GetCache().SetAssetPath("data/");

	Game game;
	pGame = &game;
	game.Initialise();

	bool canUpdateRender;
	float dTime = 0;
	while (WinUtil::Get().BeginLoop(canUpdateRender))
	{
		if (canUpdateRender /*&& dTime > 0*/)
		{
			game.Update(dTime);
			game.Render(dTime);
		}
		dTime = WinUtil::Get().EndLoop(canUpdateRender);

	}
	game.Release();
	d3d.ReleaseD3D(true);
	return 0;
}
