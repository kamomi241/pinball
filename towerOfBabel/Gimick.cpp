#include "Gimick.h"
#include <math.h>

int DragonAttack::m_graph = 0;
int DragonAttack::m_SE = 0;
int DragonAttack::m_graph_effect[9] = {0,0,0,0,0,0,0,0,0};

GimickCircle::GimickCircle(Vector2D center, double rad,double power):m_pos(center),m_rad(rad),m_power(power),m_isAttack(0) {

}

void GimickCircle::draw() {

	DrawCircleAA((float)m_pos.x, (float)m_pos.y, (float)m_rad, 100, GetColor(200, 200, 200), TRUE);
}

double GimickCircle::pointDiff(Vector2D ballpos, Vector2D ballNextpos) {


	Vector2D g = m_pos; //ギミックの中心
	double gr = m_rad;//ギミックの半径

	Vector2D ml = ballNextpos;//ボールの終点
	Vector2D m_vec = ballNextpos - ballpos;

	Vector2D o(g.x - ballpos.x, g.y - ballpos.y);//点から中心のベクトル
	Vector2D nVec = m_vec.normalizeVec();
	double t = dot(o, nVec);//点から中点の長さ
	Vector2D s = Vector2D(ballpos.x + t * nVec.x, ballpos.y + t * nVec.y);//中点
	Vector2D gs = s - g;//中心から中点のベクトル
	double gsr = gs.length();//中心から中点の長さ
	double p = sqrt(gr * gr - gsr * gsr);//中点から交点の長さ
	Vector2D c = Vector2D(p * -nVec.x + s.x, p * -nVec.y + s.y);//交点
	Vector2D r = (ballpos - c);
	double rr = r.length();

	return rr;
}

double GimickCircle::reflectionBall(Vector2D& ballpos, Vector2D& m_vec, double buffu) {

	Vector2D g = m_pos; //ギミックの中心
	double gr = m_rad;//ギミックの半径


	Vector2D ml = ballpos + m_vec;//ボールの終点

		Vector2D o(g.x - ballpos.x, g.y - ballpos.y);//点から中心のベクトル
		Vector2D nVec = m_vec.normalizeVec();
		double t = dot(o, nVec);//点から中点の長さ
		Vector2D s = Vector2D(ballpos.x + t * nVec.x, ballpos.y + t * nVec.y);//中点
		Vector2D gs = s - g;//中心から中点のベクトル
		double gsr = gs.length();//中心から中点の長さ
		double p = sqrt(gr * gr - gsr * gsr);//中点から交点の長さ
		Vector2D crossPoint = Vector2D(p * -nVec.x + s.x, p * -nVec.y + s.y);//交点


		Vector2D wall1 = crossPoint - g;
		Vector2D wallVec(-wall1.y, wall1.x);
		Vector2D newVec = crossPoint - ballpos;
		Vector2D normalVec(wallVec.x, wallVec.y);
		normalVec.normalize();
		normalVec *= dot(newVec.inverse(), normalVec);
		double power = m_vec.length();
		m_vec = normalVec + normalVec + newVec;
		m_vec = m_vec.normalizeVec() * power * 1.2;
		m_vec += wall1.normalizeVec() * m_power * 1.2;
		m_vec += wall1.normalizeVec() * power * 1.2;
		ballpos = crossPoint + (m_vec * 0.0001);
		m_vec += Vector2D(0, -2);
		m_isAttack = true;
		//DrawFormatString(20, 20, GetColor(255, 1, 1), "hit");
	return 0;
}


//ギミック当たり判定関数
bool GimickCircle::BallCollide(Vector2D g2, Vector2D m1) {
	double gr = m_rad;
	Vector2D g1 = m_pos;
	double a = (g1.x - m1.x) * (g1.x - m1.x) + (g1.y - m1.y) * (g1.y - m1.y);
	//double b = (gr + br) * (gr + br);
	double b = gr * gr;
	if (a <= b) {
		return true;
	}
	return false;
}

Vector2D GimickCircle::getPoint() {
	return m_pos;
}

void GimickCircle::setPoint(Vector2D p1) {
	m_pos = p1;
}

void GimickCircle::attackOff() {
	m_isAttack = false;
}

bool GimickCircle::getAttackSt() {
	return m_isAttack;
}


GimickWall::GimickWall(Vector2D point1, Vector2D point2) : m_pointFirst(point1),m_pointLast(point2),m_isAttack() {

}

GimickWall::~GimickWall(){}


double GimickWall::pointDiff(Vector2D p1, Vector2D p2) {
	Vector2D wallVec = m_pointLast - m_pointFirst;
	Vector2D pVec = p2 - p1;
	double b = cross(p1 - m_pointFirst, p2 - m_pointFirst) / cross(wallVec, pVec);
	double crossX = m_pointFirst.x + b * (wallVec).x;//衝突位置を特定
	double crossY = m_pointFirst.y + b * (wallVec).y;
	double diff = (crossX - p1.x) * (crossX - p1.x) + (crossY - p1.y) * (crossY - p1.y);
	return diff;
}

double GimickWall::reflectionBall(Vector2D& ballPos, Vector2D& ballVec, double buff) {
	Vector2D wallVec = m_pointLast - m_pointFirst;
	Vector2D playerNextPoint = ballPos + ballVec;
	double b = cross(ballPos - m_pointFirst, playerNextPoint - m_pointFirst) / cross(wallVec, ballVec);
	double crossX = m_pointFirst.x + b * (wallVec).x;//衝突位置を特定
	double crossY = m_pointFirst.y + b * (wallVec).y;
	Vector2D crossPoint(crossX, crossY);
	Vector2D newVec = crossPoint - ballPos;
	Vector2D FvecR = m_pointLast - m_pointFirst;
	Vector2D Fvec(-FvecR.y, FvecR.x);
	ballVec = Fvec * 0.075;
	ballPos = crossPoint + (ballVec * 0.0001);
	ballVec += Vector2D(0, -5);
	m_isAttack = true;
	//	m_vec *= -1;
	return 0.0;
}

void const GimickWall::draw() {
	DrawLineAA((float)m_pointFirst.x, (float)m_pointFirst.y, (float)m_pointLast.x, (float)m_pointLast.y, GetColor(255, 30, 30), 2);
	//DrawLineAA(m_pointFirst.x+10, m_pointFirst.y+10, m_pointLast.x+10, m_pointLast.y+10, color, 2);
}

void const GimickWall::getPoint(Vector2D& pointF, Vector2D& pointL) {
	pointF = m_pointFirst;
	pointL = m_pointLast;
}


void GimickWall::attackOff() {
	m_isAttack = false;
}

bool GimickWall::getAttackSt() {
	return m_isAttack;
}

bool GimickWall::BallCollide(Vector2D ballPos, Vector2D ballNextPos) { 
	double a = (ballPos.x - ballNextPos.x) * (m_pointFirst.y - ballPos.y) + (ballPos.y - ballNextPos.y) * (ballPos.x - m_pointFirst.x);
	if (a > 0) {
		double b = (ballPos.x - ballNextPos.x) * (m_pointLast.y - ballPos.y) + (ballPos.y - ballNextPos.y) * (ballPos.x - m_pointLast.x);
		if (a * b < 0) {
			double c = (m_pointFirst.x - m_pointLast.x) * (ballPos.y - m_pointFirst.y) + (m_pointFirst.y - m_pointLast.y) * (m_pointFirst.x - ballPos.x);
			double d = (m_pointFirst.x - m_pointLast.x) * (ballNextPos.y - m_pointFirst.y) + (m_pointFirst.y - m_pointLast.y) * (m_pointFirst.x - ballNextPos.x);
			if (c * d < 0) {
				m_isAttack = true;
				return true;
			}
		}
	}
	return false;
}


GimickArea::GimickArea(Vector2D pointF, Vector2D pointL, Vector2D pointFSub, Vector2D pointLSub):m_pointFirst(pointF),m_pointLast(pointL),m_pointFirstSub(pointFSub),m_pointLastSub(pointLSub), m_coolTime(0), m_isAttack() {

	}

GimickArea::~GimickArea(){}

bool GimickArea::BallCollide(Vector2D ballPos, Vector2D ballNextPos) {
	if (m_coolTime == 0) {
		double a = (ballPos.x - ballNextPos.x) * (m_pointFirst.y - ballPos.y) + (ballPos.y - ballNextPos.y) * (ballPos.x - m_pointFirst.x);
		if (a > 0) {
			double b = (ballPos.x - ballNextPos.x) * (m_pointLast.y - ballPos.y) + (ballPos.y - ballNextPos.y) * (ballPos.x - m_pointLast.x);
			if (a * b < 0) {
				double c = (m_pointFirst.x - m_pointLast.x) * (ballPos.y - m_pointFirst.y) + (m_pointFirst.y - m_pointLast.y) * (m_pointFirst.x - ballPos.x);
				double d = (m_pointFirst.x - m_pointLast.x) * (ballNextPos.y - m_pointFirst.y) + (m_pointFirst.y - m_pointLast.y) * (m_pointFirst.x - ballNextPos.x);
				if (c * d < 0) {
					m_isAttack = true;
					m_coolTime = 60;
					return true;
				}
			}
		}

		double e = (ballPos.x - ballNextPos.x) * (m_pointFirstSub.y - ballPos.y) + (ballPos.y - ballNextPos.y) * (ballPos.x - m_pointFirstSub.x);
		if (e > 0) {
			double f = (ballPos.x - ballNextPos.x) * (m_pointLastSub.y - ballPos.y) + (ballPos.y - ballNextPos.y) * (ballPos.x - m_pointLastSub.x);
			if (e * f < 0) {
				double g = (m_pointFirstSub.x - m_pointLastSub.x) * (ballPos.y - m_pointFirstSub.y) + (m_pointFirstSub.y - m_pointLastSub.y) * (m_pointFirstSub.x - ballPos.x);
				double h = (m_pointFirstSub.x - m_pointLastSub.x) * (ballNextPos.y - m_pointFirstSub.y) + (m_pointFirstSub.y - m_pointLastSub.y) * (m_pointFirstSub.x - ballNextPos.x);
				if (g * h < 0) {
					m_coolTime = 60;
					m_isAttack = true;
					return true;
				}
			}
		}
		return false;
	}
	else {
		return false;
	}
}




void GimickArea::decCool() {
	if (m_coolTime > 0)
		--m_coolTime;
}

void GimickArea::draw() {
	DrawLineAA((float)m_pointFirst.x, (float)m_pointFirst.y, (float)m_pointLast.x, (float)m_pointLast.y, GetColor(250, 250, 250));
	DrawLineAA((float)m_pointFirstSub.x, (float)m_pointFirstSub.y, (float)m_pointLastSub.x, (float)m_pointLastSub.y, GetColor(250, 250, 250));
}

void GimickArea::attackOff() {
	m_isAttack = false;
}

bool GimickArea::getAttackSt() {
	return m_isAttack;
}


GimickController::GimickController():m_attackNum(0),m_isDragon(false),m_dragonNum(0) {
	m_circle[0] = new GimickCircle(Vector2D(300.0, 430.0), 27, 7);
	m_circle[1] = new GimickCircle(Vector2D(390.0, 430.0), 27, 7);
	m_circle[2] = new GimickCircle(Vector2D(342.0, 510.0), 27, 7);
	m_wall[0] = new GimickWall(Vector2D(197, 662),Vector2D(153, 548));
	m_wall[1] = new GimickWall(Vector2D(372, 560),Vector2D(332, 663));
	m_area = new GimickArea(Vector2D(67,329), Vector2D(7,329), Vector2D(10,347), Vector2D(68,347));
	for (int i = 0; i < 8; i++) {
		m_dragonAttack[i] = DragonAttack();
	}
}

GimickController::~GimickController() {
	delete m_circle[0];
	delete m_circle[1];
	delete m_circle[2];
	delete m_wall[0];
	delete m_wall[1];
	delete m_area;
}


void GimickController::initialize() {
}

void GimickController::setDragon() {
	if (m_isDragon == true) {
		m_isDragon = false;
	}
	else
		m_isDragon = true;
}

void GimickController::draw() {
	/*
	for (int i = 0; i < 3; i++)
	{
		m_circle[i]->draw();
	}
	for (int j = 0; j < 2; j++)
	{
		m_wall[j]->draw();
	}
	m_area->draw();
	*/
	if (m_isDragon == true)
	{
		for (int i = 0; i < m_dragonNum; i++) {
			m_dragonAttack[i].draw();
		}
	}
}

int GimickController::updata() {
	m_attackNum = -1;
	m_area->decCool();
	if (m_area->getAttackSt() == true) {
		m_area->attackOff();
		m_attackNum = 5;
	}
	for (int i = 0; i < 3; i++)
	{
		if (m_circle[i]->getAttackSt() == true) {
			m_circle[i]->attackOff();
			m_attackNum = i;
		}
	}
	for (int j = 0; j < 2; j++)
	{
		if (m_wall[j]->getAttackSt() == true) {
			m_wall[j]->attackOff();
			m_attackNum = j + 3;
		}
	}
	if (m_isDragon == true) {
		for (int i = 0; i < m_dragonNum; i++) {
			m_dragonAttack[i].updata();
		}
	}
	return m_attackNum;
}

GimickCircle* GimickController::getCircle(int i) {
	if (i >= 0 && i < 3)
		return m_circle[i];
	return m_circle[0];
}

GimickWall* GimickController::getWall(int i) {
	if (i == 0)
		return m_wall[0];
	return m_wall[1];
}

GimickArea* GimickController::getArea() {
	return m_area;
}

void GimickController::setDragonNum(int i) {
	if (i >= 0 && i <= 8)
		m_dragonNum = i;
}

Vector2D GimickController::collideDragonAttack(Vector2D ballPos) {
	if (m_isDragon == true) {
		for (int i = 0; i < m_dragonNum; i++) {
			if (m_dragonAttack[i].collideCheck(ballPos)) {
				//反射処理
				return m_dragonAttack[i].refrect(ballPos);
			}
		}
		return Vector2D(0.0, 0.0);
	}
	else
		return Vector2D(0.0,0.0);
}

bool DragonAttack::collideCheck(Vector2D ballPos) {
	if (m_isDead == true) return false;
	double gr;
	if (m_life == 0)
		gr = 400 + 15;//大きさ
	else
		gr = 10 + 15;//大きさ
	Vector2D g1 = m_pos;
	double a = (g1.x - ballPos.x) * (g1.x - ballPos.x) + (g1.y - ballPos.y) * (g1.y - ballPos.y);
	//double b = (gr + br) * (gr + br);
	double b = gr * gr;
	if (a <= b) {
		return true;
	}
	return false;
}

Vector2D DragonAttack::refrect(Vector2D ballpos) {
	Vector2D refVec = ballpos - m_pos;
	if (m_life > 0) {
		refVec = refVec.normalizeVec() * 30.0;
		PlaySoundMem(m_SE, DX_PLAYTYPE_BACK);
		m_life = 0;
		return refVec;
	}
	else {
		double pow = 5 + 40.0 / (ballpos - m_pos).lengthSq();
		refVec = refVec.normalizeVec() * pow;
	}
	return refVec;
}

//DragonAttack
DragonAttack::DragonAttack() : 
	m_pos(),
	m_vec(),
	m_isDead(true),
	m_angle(0.0),
	m_coolTime(0),
	m_life(0)
{
	if (DragonAttack::m_graph == 0) 
		DragonAttack::m_graph = LoadGraph("texture\\cube.png");
	if (DragonAttack::m_SE == 0) 
		DragonAttack::m_SE = LoadSoundMem("effect\\san.mp3");
	if (m_graph_effect[0] == 0)
	{
		int hr = LoadDivGraph("effect\\pipo133.png", 9, 3, 3, 640, 480, m_graph_effect);
		hr++;
	}
}

DragonAttack::~DragonAttack() {

}
void DragonAttack::draw() {
	if (m_isDead == false) {
		if(m_life > 0)
			DrawRotaGraph((int)m_pos.x, (int)m_pos.y, 0.3, m_angle, m_graph, true);
		else if (m_life > -18) {
			int graphI = (int)(m_life / 2) * -1;
			DrawGraph((int)m_pos.x - 320, (int)m_pos.y - 240, m_graph_effect[graphI], true);
		}
	}
}

void DragonAttack::reset(Vector2D pos, Vector2D vec, int life) {
	m_pos = pos;
	m_vec = vec;
	m_angle = 0.0;
	m_life = life;
	m_isDead = false;
}

void DragonAttack::setCoolTime(int time) {
	m_coolTime = time;
}

int DragonAttack::getCoolTime() {
	return m_coolTime;
}

void DragonAttack::updata() {
	if (m_isDead == false)
	{
		m_life--;
		if (m_life > 0) {
			m_angle += 0.05;
			m_pos += m_vec;
			if (m_pos.y < -30.0 || m_pos.y > 800.0 || m_pos.x < -30.0 || m_pos.x > 570.0) {
				m_isDead = true;
				m_coolTime = GetRand(240);
			}
		}
		else if (m_life == 0){
				PlaySoundMem(m_SE, DX_PLAYTYPE_BACK);

		}
		else if (m_life < -18) {
			m_isDead = true;
			m_coolTime = GetRand(240);
		}
	}
	else {
		if (m_coolTime < 0) {
			float x = (float)GetRand(550);
			float vx = ((float)GetRand(200) / 100.0f);
			if (x > 250.0f)
				vx *= -1.0f;
			float vy = ((float)GetRand(400) / 100.0f) + 1.0f;

			reset(Vector2D(x, 0.0), Vector2D(vx, vy),GetRand(240) + 120);
		}
		else {
			m_coolTime--;
		}
	}
}

void GimickController::dragonReset() {
	for (int i = 0; i < m_dragonNum; i++) {
		m_dragonAttack[i].setDead();
	}
}

void DragonAttack::setDead() {
	m_isDead = true;
}

/*


void DragonEffect::set(Vector2D v) {
	m_pos = v;
	m_time = 0;
}

bool DragonEffect::draw() {
	if (m_time < 18) {
		int graphI = (int)(m_time / 2);
		DrawGraph((int)m_pos.x, (int)m_pos.y, m_graph[graphI],true);
		m_time++;
		return true;
	}
	else
		return false;
}
*/
