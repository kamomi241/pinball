#include"Startmenu.h"

Startmenu::Startmenu() {
	image_menu = LoadGraph("texture\\title.mp4");
	image1 = LoadGraph("texture\\tutorial1.png");
	image2 = LoadGraph("texture\\tutorial2.png");
	start = true;
	move = 0;
	tutorialf = false;
	page = 1;
}

bool Startmenu::Start() {
	if (start == true) {
		if (GetMovieStateToGraph(image_menu) != 1) {
			SeekMovieToGraph(image_menu, 0);
			PlayMovieToGraph(image_menu);
			WaitTimer(7);
			start = false;
		}
	}
	//スタートボタン
	if (Input::instance()->isClickedRect(60, 500, 600, 650, MOUSE_INPUT_LEFT) == TRUE) {
		return true;
	}
	//チュートリアル
	if (Input::instance()->isClickedRect(60, 700, 600, 800, MOUSE_INPUT_LEFT) == TRUE || tutorialf == true) {
		tutorialf = true;
		if (tutorial() == true)
			tutorialf = false;
	}
	else
		DrawExtendGraph(0, 0, 650, 790, image_menu, FALSE);
	return false;
}
//チュートリアル画面
bool Startmenu::tutorial() {
	if (page == 1) {
		DrawExtendGraph(0, 0, 650, 790, image1, FALSE);
	}
	else if (page == 2) {
		DrawExtendGraph(0, 0, 650, 790, image2, FALSE);
	}
	//左
	if (Input::instance()->isClickedRect(270, 700, 330, 800, MOUSE_INPUT_LEFT) == TRUE && page == 2) {
		page = 1;
		return false;
	}
	//右
	if (Input::instance()->isClickedRect(350, 700, 410, 800, MOUSE_INPUT_LEFT) == TRUE && page == 1) {
		page = 2;
		return false;
	}
	//閉じる
	if (Input::instance()->isClickedRect(550, 700, 700, 800, MOUSE_INPUT_LEFT) == TRUE) {
		page = 1;
		return true;
	}
	return false;
}