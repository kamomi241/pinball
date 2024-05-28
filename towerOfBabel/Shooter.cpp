#include "Shooter.h"

int Shooter::m_graph_base = 0;
int Shooter::m_SE = 0;
int Shooter::m_SE_charge = 0;

Shooter::Shooter():m_charge(0),m_t(0), m_isInShooter(0),m_vec(0) {
	m_graph_base = LoadGraph("texture\\shooter.png");
	if (Shooter::m_SE == 0)
		Shooter::m_SE = LoadSoundMem("effect\\shooter.mp3");
	if (Shooter::m_SE_charge == 0)
		Shooter::m_SE_charge = LoadSoundMem("effect\\charge.mp3");
}

Shooter::~Shooter(){}

void Shooter::initialize() {
	m_isInShooter = true;
	m_charge = 80;
	m_t = 0;
	m_vec = 0;
	m_pos = Vector2D(530, 675);
}

int Shooter::updata() {
	draw();
	if (m_isInShooter == true) {
		ballDraw();
		if (Input::instance()->isKeyDown(KEY_INPUT_DOWN) && m_charge < 300)
		{
			if (m_charge == 80)
			{
				PlaySoundMem(m_SE_charge, DX_PLAYTYPE_LOOP);
			}
			m_charge += 1;
		}
		if (m_charge > 110) {
			DrawBox(540, 710, 521, 700, GetColor(1, 50, 250), true);
		}
		if (m_charge > 140) {
			DrawBox(540, 710+20, 521, 700+20, GetColor(0, 200, 0), true);
		}
		if (m_charge > 170) {
			DrawBox(540, 710 + 40, 521, 700 + 40, GetColor(250, 200, 0), true);
		}
		if (m_charge > 200) {
			DrawBox(540, 710 + 60, 521, 700 + 60, GetColor(255, 50, 0), true);
		}
		if (Input::instance()->isKeyReleased(KEY_INPUT_DOWN)) {
			StopSoundMem(m_SE_charge);
			if (m_t == 0) {
				m_vec = m_charge / 2;
				m_t = 2;
				m_charge = 80;
				PlaySoundMem(m_SE, DX_PLAYTYPE_BACK);
			}
			else
				m_charge = 80;
		}
		if (m_t > 1) {
			m_t += m_vec;
			m_vec -= 1;
		}
		else if (m_vec < 0) {
			m_vec = 0;
			m_t = 0;
		}
		if (m_t > 0 && m_t < 2075) {//2175
			double y = 675 - (double)(m_t / 5.5);
			m_pos = Vector2D(530, y);
		}
		if (m_t > 2075)
		{
			StopSoundMem(m_SE_charge);
			m_isInShooter = false;
			return m_vec;
		}
	}
	return -1;
}

void Shooter::draw() {
	DrawGraph(513, 690, m_graph_base, true);
}

void Shooter::ballDraw() {
	//DrawFormatString(30, 400, GetColor(250, 250, 250), "charge: %d ball: %f %f, t: %d, vec: %d", m_charge, m_pos.x,m_pos.y,m_t,m_vec);
	DrawCircleAA((float)m_pos.x, (float)m_pos.y, 15, 30, GetColor(230, 230, 230), 1);
}

void Shooter::setIsIn(bool b) {
	m_isInShooter = b;
}

