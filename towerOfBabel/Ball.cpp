#include "Ball.h"


int Ball::m_graph_ball = 0;

bool lineCollide(const Vector2D& v1f,const Vector2D& v1l,const Vector2D& v2f,const Vector2D& v2l);

Ball::Ball(Vector2D pos) :
	m_pos(pos),
	m_vec(Vector2D()),
	m_isDead(TRUE),
	m_isInShooter(true),
	m_collideObject(),
	m_speedBuff(1.0)
{
	m_collideObject = nullptr;
	if (m_graph_ball == 0)
		m_graph_ball = LoadGraph("texture\\ball.png");
}

Ball::~Ball() {}


void Ball::setSpeedBuf(double d) {
	if (d != 0.0)
	{
		m_speedBuff = d;
	}
}

bool Ball::updata(WallController* wall, Flipper* flipper, GimickController* gimick) {
	if (m_isInShooter == false) {

		m_pos += m_vec * m_speedBuff;

		//���x�ύX
		if (m_vec.y <= 16 - 0.15)
		{
			m_vec.y += 0.15;
		}
		else if (m_vec.y > 16 + 0.01)
		{
			m_vec.y -= 0.01;
		}
		//�f�o�b�O�p
		/*

		Input* input = input->instance();
		if (input->isKeyDown(KEY_INPUT_B)) {
			Vector2D mousevec = input->getMouseVector();
			if (input->isMousePressed(MOUSE_INPUT_LEFT))
			{
				m_drawingPointFirst = mousevec;
				m_drawingPointLast = mousevec;
			}
			else if (input->isMouseKeepPressing(MOUSE_INPUT_LEFT))
			{
				m_drawingPointLast = mousevec;
			}
			else if (input->isMouseReleased(MOUSE_INPUT_LEFT))
			{
				printfDx("%.2f,%.2f^%.2f,%.2f ", m_drawingPointFirst.x, m_drawingPointFirst.y, m_drawingPointLast.x, m_drawingPointLast.y);
				m_pos = m_drawingPointFirst;
				m_vec = (m_drawingPointLast - m_drawingPointFirst) / 10.0;
				m_drawingPointFirst = Vector2D(0, 0);
				m_drawingPointLast = Vector2D(0, 0);
			}
		}

		//�����܂�
		*/
		

		m_vec += m_push;
		m_push = Vector2D();

		//�h���S���̍U���Ƃ̓����蔻��
		{
			m_vec += gimick->collideDragonAttack(m_pos);
		}

		double rate = 1.0;
		//�����̏Փ˂�����ꍇ��ԋ߂��Փ˂̂ݏ���
		//���˂��v�Z��A�ēx�Փ˂����邩�ǂ����𒲂ׁA�܂����˂�����
		//������Փ˂��Ȃ��Ȃ�܂Łi�������͂T��j�J��Ԃ��B
		while (rate > 0)
		{
			m_collideObject = nullptr;
			int collideListNum = 0;
			Vector2D playerNextPoint = m_pos + m_vec * m_speedBuff;
			//�ǂƂ̓����蔻��
			std::vector<SegmentWall*> wallList = wall->getList();
			for (auto itr = wallList.begin(); itr != wallList.end(); itr++)
			{
				SegmentWall* walls = *itr;
				Vector2D wallFirst;
				Vector2D wallLast;

				walls->getPoint(wallFirst, wallLast);
				
				if (lineCollide(wallFirst, wallLast, m_pos, playerNextPoint) == true) {//�Փ�
					//m_listCollideSegmentWall.emplace_back(wall);
					//walls->rollSet(true);
					m_list.emplace_back(walls);
					collideListNum += 1;
				}
				else{
					//walls->rollSet(false);
				}
			}
			//�t���b�p�[�Ƃ̓����蔻��

			if (flipper->getRect(1)->BallCollide(m_pos, playerNextPoint)) {
				m_list.emplace_back(flipper->getRect(1));
				collideListNum += 1;
			}
			if (flipper->getRect(0)->BallCollide(m_pos, playerNextPoint)) {
				m_list.emplace_back(flipper->getRect(0));
				collideListNum += 1;
			}
			//�M�~�b�N
			for (int i = 0; i < 3; i++)
			{
				if (gimick->getCircle(i)->BallCollide(m_pos, playerNextPoint) == true) {
					m_list.emplace_back(gimick->getCircle(i));
					collideListNum += 1;
				}
			}

			for (int i = 0; i < 2; i++)
			{
				if (gimick->getWall(i)->BallCollide(m_pos, playerNextPoint) == true) {
					m_list.emplace_back(gimick->getWall(i));
					collideListNum += 1;
				}
			}

			gimick->getArea()->BallCollide(m_pos, playerNextPoint);


			//DrawFormatString(400, 400, GetColor(200, 200, 200),"�ǂƂ̏Փː�%d", collideListNum);
			if (collideListNum >= 1)
				m_collideObject = m_list[0];
			if (collideListNum > 1) {//�����̃I�u�W�F�N�g�ƏՓ˂����������͈�ԋ߂��Փ˂݂̂��v�Z
				for (auto itr = m_list.begin(); itr != m_list.end(); itr++) {
					Object* coOb = *itr;
					if (m_collideObject->pointDiff(m_pos, playerNextPoint) > coOb->pointDiff(m_pos, playerNextPoint))
						m_collideObject = coOb;
				}
			}

			if (collideListNum >= 1) {
				rate -= 0.2;
				m_collideObject->reflectionBall(m_pos, m_vec, m_speedBuff);
				m_list.clear();
			}
			else
				rate -= 2;
		}

		//��ʊO
		if (m_pos.y > 790 || m_pos.y < -100) {
			m_isDead = FALSE;
		}
	}
	return m_isDead;
}

void const Ball::draw() {
	if (m_isInShooter == false) {
		//DrawExtendGraph((int)m_pos.x - 8, (int)m_pos.y - 8,(int)m_pos.x + 10,(int)m_pos.y + 10, m_graph_ball, TRUE);
		DrawCircleAA((float)m_pos.x, (float)m_pos.y, 15, 16, GetColor(200, 200, 200), TRUE);
		DrawPixel((int)m_pos.x, (int)m_pos.y, GetColor(250, 10, 10));
		//DrawFormatString(10, 250, GetColor(255, 255, 255), "pos:%f %f vec:%f %f", m_pos.x, m_pos.y, m_vec.x, m_vec.y);
	}
}

void Ball::setShooter(bool b) {
	m_isInShooter = b;
}

void Ball::push(Vector2D vec) {
	m_push += vec;
}

bool lineCollide(const Vector2D& v1f,const Vector2D& v1l,const Vector2D& v2f,const Vector2D& v2l) {
	double a = (v2f.x - v2l.x) * (v1f.y - v2f.y) + (v2f.y - v2l.y) * (v2f.x - v1f.x);
	if (a > 0) {
		double b = (v2f.x - v2l.x) * (v1l.y - v2f.y) + (v2f.y - v2l.y) * (v2f.x - v1l.x);
		if (a * b < 0) {
			double c = (v1f.x - v1l.x) * (v2f.y - v1f.y) + (v1f.y - v1l.y) * (v1f.x - v2f.x);
			double d = (v1f.x - v1l.x) * (v2l.y - v1f.y) + (v1f.y - v1l.y) * (v1f.x - v2l.x);
			if (c * d < 0) return true;
		}
	}
	return false;
}

void Ball::setPos(Vector2D pos) {
	m_pos = pos;
}

/*
bool TriangleCollide(Triangle& tri,Vector2D ballPos,Vector2D ballNextPos) {
	Vector2D t1;
	Vector2D t2;
	Vector2D t3;
	bool posIsIn = false;//ballPos�����ɂ��邩�ǂ���
	bool nextPosIsIn = false;//ballNextPos�����ɂ��邩�ǂ���
	tri.getPoint(t1, t2, t3);
	double a1 = cross(t2 - t1, ballPos - t1);
	double a2 = cross(t3 - t2, ballPos - t2);
	double a3 = cross(t1 - t3, ballPos - t3);
	if (a1 < 0 && a2 < 0 && a3 < 0)
		posIsIn = true;

	double b1 = cross(t2 - t1, ballNextPos - t1);
	double b2 = cross(t3 - t2, ballNextPos - t2);
	double b3 = cross(t1 - t3, ballNextPos - t3);
	if (b1 < 0 && b2 < 0 && b3 < 0)
		nextPosIsIn = true;
	if (posIsIn == true || nextPosIsIn == true) 
		return true;
	return false;
}
*/

