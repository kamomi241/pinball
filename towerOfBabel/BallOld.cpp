#include "Ball.h"
#include "Vector2D.h"
#include "Input.h"
#include "DxLib.h"

int Ball::m_graph_ball = 0;

Ball::Ball(Vector2D pos) :
	m_pos(pos),
	m_vec(Vector2D()),
	m_isDead(TRUE)
{
	if (m_graph_ball == 0)
		m_graph_ball = LoadGraph("texture\\ball.png");
}

Ball::~Ball() {}

bool Ball::updata() {
	if (m_vec.y <= 8 - 0.08) {
		m_vec.y += 0.08;
	}
	else if (m_vec.y > 8 + 0.08) {
		m_vec.y -= 0.01;
	}
	m_pos += m_vec;

	

	if (m_pos.y > 780) {
		m_isDead = FALSE;
	}
	return m_isDead;
}

void const Ball::draw() {
	DrawGraph((int)m_pos.x, (int)m_pos.y, m_graph_ball, TRUE);
	DrawFormatString(10, 200, GetColor(255, 255, 255), "pos:%f %f vec:%f %f", m_pos.x, m_pos.y, m_vec.x, m_vec.y);
}

void Ball::push(Vector2D vec) {
	m_vec += vec;
}