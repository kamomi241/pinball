#include "DxLib.h"
#include "Game.h"



constexpr int WINDOW_WIDTH = 650;
constexpr int WINDOW_HEIGHT = 790;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR IpCmdLine, _In_ int nCmdShow)
{
	SetWindowText("pinball");
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	ChangeWindowMode(TRUE);

	//垂直同期するかの切り替え(スクリーン更新速度に合わせる。)
	//SetWaitVSyncFlag(FALSE);

	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	Game* ptr_Game = nullptr;
	ptr_Game = new Game(WINDOW_WIDTH, WINDOW_HEIGHT);
	ptr_Game->initialize();

	while (true)
	{

		if (ProcessMessage() != 0) break;

		ClearDrawScreen();

		if (ptr_Game->updata() == FALSE)
			break;



		if (CheckHitKey(KEY_INPUT_L) == 1)
			clsDx();





		ScreenFlip();
	}
	delete ptr_Game;


	DxLib_End();

	return 0;
}