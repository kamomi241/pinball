#pragma once

#include "Input.h"
#include "DxLib.h"
#include "Ball.h"
#include "Wall.h"
#include "Shooter.h"

#include "clear.h"
#include "Startmenu.h"
#include "Select.h"
#include "Boss.h"

class Game{
public:
	Game(int width, int height);
	~Game();
	void initialize();

	bool updata();

	enum class GameState : char
	{
		Load,
		Title,
		NewgameMenu,
		ContinueMenu,
		PlayingGame,
		Clear,
		Select
	};

	void gameStart();

private:
	//時間計測
	LONGLONG m_nowTime;
	LONGLONG m_oldTime;
	//ポインタ達
	Input* m_ptr_input;
	Ball* m_ptr_ball;
	WallController* m_ptr_wallController;
	GimickController* m_ptr_gimickController;
	Flipper* m_ptr_flipper;
	Shooter* m_ptr_shooter;
	int score;

	int m_life;

	int m_shootP;

	int times;

	Boss* m_ptr_boss;
	Clear* m_ptr_clear;
	Startmenu* m_ptr_start;
	Select* m_ptr_select;

	int bossmove;
	int damege, type;
	int stock[6];
	int hit;

	//ゲーム状態
	bool m_gameRunning;
	GameState m_gameState;

	//画面の大きさ
	int m_width;
	int m_height;

	//画像のロード
	int m_graph_title;
	int m_graph_stageSelect;
	int m_graph_back;
	int m_graph_hart;
	//音声
	int battle_bgm;
	bool start;
};
