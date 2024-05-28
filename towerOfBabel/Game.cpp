#include "Game.h"

#include "DxLib.h"
#include "Input.h"
#include <cmath>

Game::Game(int width, int height) :
	m_width(width),
	m_height(height),
	m_gameRunning(TRUE),
	m_gameState(GameState::Load),
	m_ptr_input(nullptr),
	m_ptr_ball(nullptr),
	m_ptr_wallController(nullptr),
	m_ptr_shooter(nullptr),
	m_graph_title(0),
	m_graph_stageSelect(0),
	m_nowTime(0),
	m_oldTime(0),
	m_life(0),
	m_shootP(0),
	m_ptr_select(0),
	m_ptr_start(0),
	stock(),
	damege(),
	hit(),
	m_graph_back(),
	m_ptr_boss(),
	m_ptr_clear(),
	m_ptr_flipper(),
	m_ptr_gimickController(),
	times(),
	type(),
	score(0)
{
	
}

Game::~Game()
{
	Input::destroy();

	delete m_ptr_boss;
	delete m_ptr_start;
	delete m_ptr_select;
	delete m_ptr_clear;

	if (m_ptr_ball != nullptr)
		delete m_ptr_ball;
	if (m_ptr_shooter != nullptr)
		delete m_ptr_shooter;
	if (m_ptr_wallController != nullptr)
		delete m_ptr_wallController;
	if (m_ptr_flipper != nullptr)
		delete m_ptr_flipper;
	if (m_ptr_gimickController != nullptr)
		delete m_ptr_gimickController;
}

void Game::initialize()
{
	m_nowTime = GetNowHiPerformanceCount();

	SRand(clock());

	//クラスのポインタ設定
	Input::create();
	m_ptr_input = Input::instance();

	//音声
	battle_bgm = LoadSoundMem("effect\\bossbgm.mp3");
	start = true;

	//画像の読込
	m_graph_title = LoadGraph("texture\\Title.png");
	m_graph_stageSelect = LoadGraph("texture\\StageSelect.png");
	m_graph_back = LoadGraph("texture\\game_back.png");
	m_graph_hart = LoadGraph("texture\\hart.png");
	m_ptr_boss = new Boss();

	//変数の初期化
	m_gameState = GameState::Title;
	m_ptr_start = new Startmenu();
	damege = 0, type = 0;
}

void Game::gameStart() {
	m_ptr_clear = new Clear();
	m_ptr_select = new Select();
	stock[0] = 0;
	stock[1] = 0;
	stock[2] = 0;
	stock[3] = 6;
	stock[4] = 6;
	stock[5] = 12;
	hit = -1;
	score = 0;
	bossmove = 0;

	m_ptr_ball = new Ball(Vector2D(300, 30));
	m_ptr_wallController = new WallController();
	m_ptr_wallController->loadWall();

	m_ptr_flipper = new Flipper(185.0, 320.0, 743.0);
	m_ptr_flipper->initialize();

	m_ptr_gimickController = new GimickController();
	m_ptr_gimickController->initialize();

	m_ptr_shooter = new Shooter();
	m_ptr_shooter->initialize();
	m_life = 3;
}

bool Game::updata()
{
	 //FPSを固定したい時
	LONGLONG endTime = 16666 + m_oldTime;
	while (GetNowHiPerformanceCount() < endTime)
	{
		WaitTimer(1);
	}
	

	//FPS表示
	m_nowTime = GetNowHiPerformanceCount();
	double frameTime = (m_nowTime - m_oldTime) / 1000000.0f;
	double FPS = 1 / frameTime;
	m_oldTime = m_nowTime;

	m_ptr_input->keyboardCheck();
	m_ptr_input->mouseCheck();
	char test{};

	if (m_ptr_input->isKeyPressed(KEY_INPUT_9))
	{
		m_gameRunning = false;
	}

	switch (m_gameState)
	{
	case GameState::Load:
		break;

	case GameState::Title:
		DrawGraph(0, 0, m_graph_title, FALSE);
		//DrawString(m_width / 2 - 30, 400, "LEFT CLICK", GetColor(255, 255, 255));
		//if (m_ptr_input->isMousePressed(MOUSE_INPUT_LEFT))
		if (m_ptr_start->Start() == true)
		{
			m_gameState = GameState::PlayingGame;
			m_ptr_input->inputStatsReset();
			gameStart();
		}
		break;

	case GameState::PlayingGame:
		if(bossmove == 201) m_ptr_flipper->setReverse(2);
		else if(bossmove == 204)m_ptr_flipper->setReverse(4);
		else m_ptr_flipper->setReverse(0);
		if(bossmove == 202) m_ptr_ball->setSpeedBuf(0.5);
		else if(bossmove == 203) m_ptr_ball->setSpeedBuf(2.0);
		else if(bossmove == 205)m_ptr_ball->setSpeedBuf(0.001);
		else m_ptr_ball->setSpeedBuf(1.0);
		DrawGraph(0, 200, m_graph_back, true);
		DrawExtendGraph(270, 400, 330, 460, m_ptr_select->gimmick[stock[0]], TRUE);
		DrawExtendGraph(360, 400, 420, 460, m_ptr_select->gimmick[stock[1]], TRUE);
		DrawExtendGraph(312, 480, 372, 540, m_ptr_select->gimmick[stock[2]], TRUE);
		DrawExtendGraph(120, 570, 190, 670, m_ptr_select->gimmick[stock[3]], TRUE);
		DrawExtendGraph(405, 570, 335, 670, m_ptr_select->gimmick[stock[4]], TRUE);
		DrawExtendGraph( 10, 330,  75, 350, m_ptr_select->gimmick[stock[5]], TRUE);
		if (start == true) {
			//bgm再生
			PlaySoundMem(battle_bgm, DX_PLAYTYPE_LOOP, TRUE);
			start = false;
		}
		//m_ptr_wallController->updata();
		m_ptr_flipper->updata();

		m_shootP = m_ptr_shooter->updata();
		if (m_shootP != -1)
		{
			m_ptr_ball->setPos(Vector2D(528, 330));
			if (m_shootP < 5)
				m_shootP = 5;
			m_ptr_ball->push(Vector2D(0.0, ( - 6.0) - m_shootP / 4));
			m_ptr_ball->setShooter(false);
			m_ptr_shooter->setIsIn(false);
		}
		if (m_ptr_ball->updata(m_ptr_wallController, m_ptr_flipper, m_ptr_gimickController) == FALSE) {
			delete m_ptr_ball;
			m_ptr_ball = new Ball(Vector2D(390.0, 300));
			m_ptr_ball->setShooter(true);
			m_ptr_shooter->initialize();
			m_life -= 1;
		}
		if (m_life <= 0) {
			StopSoundMem(battle_bgm);
			start = true;
			m_gameState = GameState::Clear;
		}
		hit = m_ptr_gimickController->updata();
		//DrawFormatString(30, 232, GetColor(250, 250, 250), "%f,%f", m_ptr_input->getMouseX(), m_ptr_input->getMouseY());
		if (m_ptr_input->isKeyPressed(KEY_INPUT_8))
		{
			m_ptr_shooter->initialize();
		}


		m_ptr_ball->draw();
		m_ptr_flipper->draw();
		m_ptr_gimickController->draw();

		//*m_ptr_boss->getkillcount() = 4;

		if (m_ptr_boss->update(&times, stock, hit,&score,&m_life,&bossmove) == true) {
			StopSoundMem(battle_bgm);
			start = true;
			if (*m_ptr_boss->getkillcount() == 4) {
				m_ptr_gimickController->setDragon();
				m_ptr_gimickController->setDragonNum(8);
			}
			if (*m_ptr_boss->getkillcount() < 5) {
				score += 50000;
				if(m_life != 3) m_life++;
				score += m_life * 3333;
				m_gameState = GameState::Select;
			}
			else {
				m_gameState = GameState::Clear;
			}
		}
		//体力表示
		if (m_life >= 1) {
			DrawExtendGraph(570, 570, 650, 650, m_graph_hart, TRUE);
		}
		if (m_life >= 2) {
			DrawExtendGraph(570, 490, 650, 570, m_graph_hart, TRUE);
		}
		if (m_life >= 3) {
			DrawExtendGraph(570, 410, 650, 490, m_graph_hart, TRUE);
		}
		break;
	case GameState::Select:
		if (m_ptr_select->make(*m_ptr_boss->getkillcount(), times, stock) == true) {

			m_gameState = GameState::PlayingGame;
			delete m_ptr_ball;
			m_ptr_ball = new Ball(Vector2D(390.0, 300));
			m_ptr_ball->setShooter(true);
			m_ptr_shooter->initialize();
		}
		break;
	case GameState::Clear:
		if (m_ptr_clear->Score(&score,m_life) == true) {
			*m_ptr_boss->getkillcount() = 0;
			times = 0;
			m_ptr_boss->start(m_life);
			m_gameState = GameState::Title;
		}
		break;
	}
	//DrawFormatString(10, 42, GetColor(255, 1, 1), "FPS %.2f", FPS);

	return m_gameRunning;
}